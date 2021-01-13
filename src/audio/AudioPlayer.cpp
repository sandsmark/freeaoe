#include "AudioPlayer.h"

#include "core/Utility.h"

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>
#include <filesystem>

#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "sts_mixer.h"
#include "global/Config.h"

#include <genie/util/Utility.h>
#include <genie/dat/Sound.h>
#include <genie/dat/SoundItem.h>
#include <stddef.h>

#include <miniaudio/extras/dr_mp3.h>

#define MA_NO_JACK
#define MA_NO_SDL
#define MA_NO_OPENAL

// the miniaudio pulseaudio backend is broken, so fall back to the pulseaudio alsa emulation for now
//#define MA_NO_ALSA
#define MA_NO_PULSEAUDIO
//#define ma_DEBUG_OUTPUT
#include <miniaudio/miniaudio.h>

#ifndef DRMP3_MIN_DATA_CHUNK_SIZE
#define DRMP3_MIN_DATA_CHUNK_SIZE   1024
#endif
#ifndef DRMP3_DATA_CHUNK_SIZE
#define DRMP3_DATA_CHUNK_SIZE  DRMP3_MIN_DATA_CHUNK_SIZE*4
#endif

void AudioPlayer::malCallback(ma_device *device, void *buffer, const void* /*input*/, uint32_t frameCount)
{
    AudioPlayer *that = reinterpret_cast<AudioPlayer*>(device->pUserData);

    if (!that->m_mutex.try_lock()) {
        WARN << "Failed to lock mutex, probably shutting down";
        return;
    }
    sts_mixer_mix_audio(that->m_mixer.get(), buffer, frameCount);
    that->m_mutex.unlock();
}

void AudioPlayer::mp3Callback(sts_mixer_sample_t *sample, void *userdata)
{
    ma_decoder* decoder = reinterpret_cast<ma_decoder*>(userdata);
    REQUIRE(decoder, return);

    sample->length = ma_decoder_read_pcm_frames(decoder, sample->audiodata, DRMP3_MIN_DATA_CHUNK_SIZE) * 2;
}

void AudioPlayer::mp3StopCallback(const int id, sts_mixer_sample_t *sample, void *userdata)
{
    (void)sample;

    ma_decoder* decoder = reinterpret_cast<ma_decoder*>(userdata);
    ma_decoder_uninit(decoder);
    delete decoder;

    std::unordered_map<std::string, int>::iterator it = instance().m_activeStreams.begin();
    for (; it != instance().m_activeStreams.end(); it++) {
        if (it->second == id) {
            DBG << it->first << "stopped";
            instance().m_activeStreams.erase(it);
            return;
        }
    }
    WARN << "Failed to find" << id << "in active streams";
}

AudioPlayer::AudioPlayer() :
    m_mixer(std::make_unique<sts_mixer_t>())
{
    sts_mixer_init(m_mixer.get(), 44100, STS_MIXER_SAMPLE_FORMAT_16);
    onMusicVolumeChanged();
    onSoundVolumeChanged();


    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_s16;
    config.playback.channels = 2;
    config.sampleRate        = 44100;
    config.dataCallback      = &AudioPlayer::malCallback;
    config.pUserData         = this;

    m_device = std::make_unique<ma_device>();
    ma_result ret = ma_device_init(nullptr, &config, m_device.get());
    if (ret != MA_SUCCESS) {
        WARN << "Failed to open playback device" << ret;
        return;
    }

    ret = ma_device_start(m_device.get());
    if (ret != MA_SUCCESS) {
        WARN << "Failed to start playback device." << ret;
        ma_device_uninit(m_device.get());
        return;
    }

    Config::Inst().connect(Config::SoundVolume, this, &AudioPlayer::onSoundVolumeChanged);
    Config::Inst().connect(Config::MusicVolume, this, &AudioPlayer::onMusicVolumeChanged);
}

AudioPlayer::~AudioPlayer()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    ma_device_uninit(m_device.get());
    sts_mixer_shutdown(m_mixer.get());
}

void AudioPlayer::playSound(const AudioPlayer::StandardSound id, const float pan, const float volume)
{
    int fileID = -1;
    switch(id) {
    case TributeSound:
        fileID = AssetManager::filenameID("tribute.wav");
        break;
    }

    if (fileID < 0) {
        DBG << "Didn't find standard sound for" << id;
        return;
    }

    std::shared_ptr<uint8_t[]> wavPtr = AssetManager::Inst()->getWavPtr(fileID);
    if (!wavPtr) {
        WARN << "failed to get wav data for" << fileID;
        return;
    }

    playSample(wavPtr, pan, volume);
}

struct WavHeader {
    enum AudioFormats {
        PCM = 0x1,
        ADPCM = 0x2,
        IEEEFloat = 0x3,
        ALaw = 0x6,
        MULaw = 0x7,
        DVIADPCM = 0x11,
        AAC = 0xff,
        WWISE = 0xffffu,
    };

    // RIFF header
    uint32_t ChunkID;
    uint32_t ChunkSize;
    uint32_t Format;

    // fmt subchunk
    uint32_t Subchunk1ID;
    uint32_t Subchunk1Size;

    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;

    // data subchunk
    uint32_t Subchunk2ID;
    uint32_t Subchunk2Size;
};



void AudioPlayer::playSample(const std::shared_ptr<uint8_t[]> &data, const float pan, const float volume)
{
    if (!m_mixer || !m_device) {
        return;
    }

    WavHeader *header = reinterpret_cast<WavHeader*>(data.get());
    if (memcmp(data.get(), "RIFF", 4) != 0) {
        WARN << "Invalid chunk header";
        return;
    }

    if (header->AudioFormat != WavHeader::PCM) {
        WARN << "Can only play PCM, got audio format" << header->AudioFormat;
        WARN << header->Format;
        WARN << "Channels" << header->NumChannels;
        WARN << header->ChunkID;
        return;
    }

    if (header->NumChannels != 1) {
        WARN << "can only play mono samples";
        return;
    }

    int audioFormat = 0;

    if (header->BitsPerSample == 8) {
        audioFormat = STS_MIXER_SAMPLE_FORMAT_8;
    } else if (header->BitsPerSample == 16) {
        audioFormat = STS_MIXER_SAMPLE_FORMAT_16;
    } else if (header->BitsPerSample == 32) {
        audioFormat = STS_MIXER_SAMPLE_FORMAT_32;
    } else {
        WARN << "Unsupported sample format" << header->BitsPerSample;
        return;
    }

    sts_mixer_sample_t *sample = new sts_mixer_sample_t;
    sample->audio_format = audioFormat;
    sample->frequency = header->SampleRate;
    sample->length = (header->Subchunk2Size / (header->BitsPerSample/8)) - sizeof(WavHeader);
    sample->data = data;
    sample->audiodata = data.get() + sizeof(WavHeader);

    const float pitch = 1.f;

    std::lock_guard<std::mutex> guard(m_mutex);
    if (sts_mixer_play_sample(m_mixer.get(), sample, volume, pitch, pan) < 0) {
        WARN << "unable to play sample, too many playing already";
        delete sample;
    }
}

void AudioPlayer::playSound(const int id, const int civilization, const float pan, const float volume)
{
    const genie::Sound &sound = DataManager::Inst().getSound(id);
    if (sound.Items.empty()) {
        WARN << "no sounds";
        return;
    }


    std::vector<int16_t> probabilities;
    for (const genie::SoundItem &item : sound.Items) {
        if (item.Civilization != civilization) {
            probabilities.push_back(0);
        } else {
            probabilities.push_back(item.Probability);
        }
    }

    static std::mt19937 gen((std::random_device())());
    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
    const size_t selected = dist(gen);

    const int wavId = sound.Items[selected].ResourceID;
    if (wavId < 0) {
        WARN << "FIXME: load external sounds";
        return;
    }

//    DBG << "playing" << sound.Items[selected].FileName;

    std::shared_ptr<uint8_t[]> wavPtr = AssetManager::Inst()->getWavPtr(wavId);
    if (!wavPtr) {
        WARN << "failed to get wav data for" << wavId;
        return;
    }

    playSample(wavPtr, pan, volume);
}


// :%s-#define \([^ ]*\) .*-case \1: return "\1";-
inline std::string maErrorString(const ma_result result)
{
    switch(result) {

    case MA_SUCCESS: return "MA_SUCCESS";
    case MA_ERROR: return "MA_ERROR";
    case MA_INVALID_ARGS: return "MA_INVALID_ARGS";
    case MA_INVALID_OPERATION: return "MA_INVALID_OPERATION";
    case MA_OUT_OF_MEMORY: return "MA_OUT_OF_MEMORY";
    case MA_OUT_OF_RANGE: return "MA_OUT_OF_RANGE";
    case MA_ACCESS_DENIED: return "MA_ACCESS_DENIED";
    case MA_DOES_NOT_EXIST: return "MA_DOES_NOT_EXIST";
    case MA_ALREADY_EXISTS: return "MA_ALREADY_EXISTS";
    case MA_TOO_MANY_OPEN_FILES: return "MA_TOO_MANY_OPEN_FILES";
    case MA_INVALID_FILE: return "MA_INVALID_FILE";
    case MA_TOO_BIG: return "MA_TOO_BIG";
    case MA_PATH_TOO_LONG: return "MA_PATH_TOO_LONG";
    case MA_NAME_TOO_LONG: return "MA_NAME_TOO_LONG";
    case MA_NOT_DIRECTORY: return "MA_NOT_DIRECTORY";
    case MA_IS_DIRECTORY: return "MA_IS_DIRECTORY";
    case MA_DIRECTORY_NOT_EMPTY: return "MA_DIRECTORY_NOT_EMPTY";
    case MA_END_OF_FILE: return "MA_END_OF_FILE";
    case MA_NO_SPACE: return "MA_NO_SPACE";
    case MA_BUSY: return "MA_BUSY";
    case MA_IO_ERROR: return "MA_IO_ERROR";
    case MA_INTERRUPT: return "MA_INTERRUPT";
    case MA_UNAVAILABLE: return "MA_UNAVAILABLE";
    case MA_ALREADY_IN_USE: return "MA_ALREADY_IN_USE";
    case MA_BAD_ADDRESS: return "MA_BAD_ADDRESS";
    case MA_BAD_SEEK: return "MA_BAD_SEEK";
    case MA_BAD_PIPE: return "MA_BAD_PIPE";
    case MA_DEADLOCK: return "MA_DEADLOCK";
    case MA_TOO_MANY_LINKS: return "MA_TOO_MANY_LINKS";
    case MA_NOT_IMPLEMENTED: return "MA_NOT_IMPLEMENTED";
    case MA_NO_MESSAGE: return "MA_NO_MESSAGE";
    case MA_BAD_MESSAGE: return "MA_BAD_MESSAGE";
    case MA_NO_DATA_AVAILABLE: return "MA_NO_DATA_AVAILABLE";
    case MA_INVALID_DATA: return "MA_INVALID_DATA";
    case MA_TIMEOUT: return "MA_TIMEOUT";
    case MA_NO_NETWORK: return "MA_NO_NETWORK";
    case MA_NOT_UNIQUE: return "MA_NOT_UNIQUE";
    case MA_NOT_SOCKET: return "MA_NOT_SOCKET";
    case MA_NO_ADDRESS: return "MA_NO_ADDRESS";
    case MA_BAD_PROTOCOL: return "MA_BAD_PROTOCOL";
    case MA_PROTOCOL_UNAVAILABLE: return "MA_PROTOCOL_UNAVAILABLE";
    case MA_PROTOCOL_NOT_SUPPORTED: return "MA_PROTOCOL_NOT_SUPPORTED";
    case MA_PROTOCOL_FAMILY_NOT_SUPPORTED: return "MA_PROTOCOL_FAMILY_NOT_SUPPORTED";
    case MA_ADDRESS_FAMILY_NOT_SUPPORTED: return "MA_ADDRESS_FAMILY_NOT_SUPPORTED";
    case MA_SOCKET_NOT_SUPPORTED: return "MA_SOCKET_NOT_SUPPORTED";
    case MA_CONNECTION_RESET: return "MA_CONNECTION_RESET";
    case MA_ALREADY_CONNECTED: return "MA_ALREADY_CONNECTED";
    case MA_NOT_CONNECTED: return "MA_NOT_CONNECTED";
    case MA_CONNECTION_REFUSED: return "MA_CONNECTION_REFUSED";
    case MA_NO_HOST: return "MA_NO_HOST";
    case MA_IN_PROGRESS: return "MA_IN_PROGRESS";
    case MA_CANCELLED: return "MA_CANCELLED";
    case MA_MEMORY_ALREADY_MAPPED: return "MA_MEMORY_ALREADY_MAPPED";
    case MA_AT_END: return "MA_AT_END";
    
    /* General miniaudio-specific errors. */
    case MA_FORMAT_NOT_SUPPORTED: return "MA_FORMAT_NOT_SUPPORTED";
    case MA_DEVICE_TYPE_NOT_SUPPORTED: return "MA_DEVICE_TYPE_NOT_SUPPORTED";
    case MA_SHARE_MODE_NOT_SUPPORTED: return "MA_SHARE_MODE_NOT_SUPPORTED";
    case MA_NO_BACKEND: return "MA_NO_BACKEND";
    case MA_NO_DEVICE: return "MA_NO_DEVICE";
    case MA_API_NOT_FOUND: return "MA_API_NOT_FOUND";
    case MA_INVALID_DEVICE_CONFIG: return "MA_INVALID_DEVICE_CONFIG";
    
    /* State errors. */
    case MA_DEVICE_NOT_INITIALIZED: return "MA_DEVICE_NOT_INITIALIZED";
    case MA_DEVICE_ALREADY_INITIALIZED: return "MA_DEVICE_ALREADY_INITIALIZED";
    case MA_DEVICE_NOT_STARTED: return "MA_DEVICE_NOT_STARTED";
    case MA_DEVICE_NOT_STOPPED: return "MA_DEVICE_NOT_STOPPED";
    
    /* Operation errors. */
    case MA_FAILED_TO_INIT_BACKEND: return "MA_FAILED_TO_INIT_BACKEND";
    case MA_FAILED_TO_OPEN_BACKEND_DEVICE: return "MA_FAILED_TO_OPEN_BACKEND_DEVICE";
    case MA_FAILED_TO_START_BACKEND_DEVICE: return "MA_FAILED_TO_START_BACKEND_DEVICE";
    case MA_FAILED_TO_STOP_BACKEND_DEVICE: return "MA_FAILED_TO_STOP_BACKEND_DEVICE";
    default: return "Unknown";
    }
}

void AudioPlayer::playStream(const std::string &filename)
{
    std::string filePath = AssetManager::Inst()->locateStreamFile(filename);
    if (filePath.empty()) {
        WARN << "Unable to find" << filename;
        return;
    }

    ma_decoder_config decoderConfig = ma_decoder_config_init(ma_format_unknown, 2, 0);
    decoderConfig.channelMap[0] = MA_CHANNEL_LEFT;
    decoderConfig.channelMap[1] = MA_CHANNEL_RIGHT;
    std::unique_ptr<ma_decoder> mp3Decoder = std::make_unique<ma_decoder>();
    ma_result result = ma_decoder_init_file_mp3(filePath.c_str(), &decoderConfig, mp3Decoder.get());
    if (result != MA_SUCCESS) {
        WARN << "Failed to init MP3 decoder for" << filePath << maErrorString(result);
        return;
    }

    std::unique_ptr<sts_mixer_stream_t> stream = std::make_unique<sts_mixer_stream_t>();
    stream->callback = &AudioPlayer::mp3Callback;
    stream->stop_callback = &AudioPlayer::mp3StopCallback;

    size_t bytesPerFrame = mp3Decoder->outputChannels;
    switch(mp3Decoder->outputFormat) {
    case ma_format_u8:
        bytesPerFrame *= 1;
        stream->sample.audio_format = STS_MIXER_SAMPLE_FORMAT_8;
        break;
    case ma_format_s16:
        bytesPerFrame *= 2;
        stream->sample.audio_format = STS_MIXER_SAMPLE_FORMAT_16;
        break;
    case ma_format_s32:
        bytesPerFrame *= 4;
        stream->sample.audio_format = STS_MIXER_SAMPLE_FORMAT_32;
        break;
    case ma_format_f32:
        bytesPerFrame *= 4;
        stream->sample.audio_format = STS_MIXER_SAMPLE_FORMAT_FLOAT;
        break;
    default:
        WARN << "Invalid decoded format" << decoderConfig.format;
        return;
    }

    stream->sample.frequency = mp3Decoder->outputSampleRate;
    stream->sample.length = 0; // force a fetch on first play
    stream->sample.data = std::shared_ptr<uint8_t[]>(new uint8_t[DRMP3_DATA_CHUNK_SIZE * bytesPerFrame]);
    stream->sample.audiodata = stream->sample.data.get();

    stream->userdata = mp3Decoder.get();

    int id = sts_mixer_play_stream(m_mixer.get(), stream.get(), 0.5);
    if (id < 0) {
        WARN << "unable to play sample, too many playing already";
        return;
    }
    m_activeStreams[filename] = id;

    stream.release();
    mp3Decoder.release();
}

void AudioPlayer::stopStream(const std::string &filename)
{
    if (!m_activeStreams.contains(filename)) {
        WARN << filename << "is not playing";
        return;
    }

    m_mutex.lock();
    sts_mixer_stop_voice(m_mixer.get(), m_activeStreams[filename]);
    m_mutex.unlock();
}

AudioPlayer &AudioPlayer::instance()
{
    static AudioPlayer inst;
    return inst;
}

void AudioPlayer::onSoundVolumeChanged()
{
    if (!Config::Inst().isOptionSet(Config::SoundVolume)) {
        return;
    }

    float volume = m_mixer->sample_gain;
    try {
        volume = std::stof(Config::Inst().getValue(Config::SoundVolume));
    } catch (const std::exception &) {
        volume = m_mixer->sample_gain;
    } //idgaf
    m_mixer->sample_gain = std::clamp(volume, 0.f, 1.f);

}

void AudioPlayer::onMusicVolumeChanged()
{
    if (!Config::Inst().isOptionSet(Config::MusicVolume)) {
        return;
    }
    float volume = m_mixer->stream_gain;
    try {
        volume = std::stof(Config::Inst().getValue(Config::MusicVolume));
    } catch (const std::exception &) {
        volume = m_mixer->stream_gain;
    } //idgaf
    m_mixer->stream_gain = std::clamp(volume, 0.f, 1.f);
}
