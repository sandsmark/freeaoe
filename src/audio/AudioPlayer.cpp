#include "AudioPlayer.h"

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>

#include "core/Logger.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "sts_mixer.h"

#include <genie/dat/Sound.h>
#include <genie/dat/SoundItem.h>
#include <stddef.h>


#include <miniaudio/extras/dr_mp3.h>

#define MA_NO_JACK
#define MA_NO_SDL
#define MA_NO_OPENAL
#define MA_NO_ALSA
//#define ma_DEBUG_OUTPUT
#include <miniaudio/miniaudio.h>

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
    if (!decoder) {
        WARN << "No decoder!";
        return;
    }

    sample->length = ma_decoder_read_pcm_frames(decoder, sample->audiodata, DRMP3_SRC_CACHE_SIZE_IN_FRAMES) * 2;
}

void AudioPlayer::mp3StopCallback(sts_mixer_sample_t *sample, void *userdata)
{
    ma_decoder* decoder = reinterpret_cast<ma_decoder*>(userdata);
    ma_decoder_uninit(decoder);
    delete decoder;
}

AudioPlayer::AudioPlayer()
{
    m_mixer = std::make_unique<sts_mixer_t>();
    sts_mixer_init(m_mixer.get(), 44100, STS_MIXER_SAMPLE_FORMAT_16);


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
}

AudioPlayer::~AudioPlayer()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    ma_device_uninit(m_device.get());
    sts_mixer_shutdown(m_mixer.get());
}

struct WavHeader {
    // RIFF header
    uint32_t ChunkID;
    uint32_t ChunkSize;
    uint32_t Format;

    // fmt subchunk
    uint32_t Subchunk1ID;
    uint32_t Subchunk1Size;

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

    if (header->AudioFormat != WavHeader::PCM) {
        WARN << "Can only play PCM, got audio format" << header->AudioFormat;
        WARN << header->Format;
        WARN << header->NumChannels;
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

        /* General errors. */
    case MA_ERROR: return "MA_ERROR";
    case MA_INVALID_ARGS: return "MA_INVALID_ARGS";
    case MA_INVALID_OPERATION: return "MA_INVALID_OPERATION";
    case MA_OUT_OF_MEMORY: return "MA_OUT_OF_MEMORY";
    case MA_ACCESS_DENIED: return "MA_ACCESS_DENIED";
    case MA_TOO_LARGE: return "MA_TOO_LARGE";
    case MA_TIMEOUT: return "MA_TIMEOUT";

        /* General miniaudio-specific errors. */
    case MA_FORMAT_NOT_SUPPORTED: return "MA_FORMAT_NOT_SUPPORTED";
    case MA_DEVICE_TYPE_NOT_SUPPORTED: return "MA_DEVICE_TYPE_NOT_SUPPORTED";
    case MA_SHARE_MODE_NOT_SUPPORTED: return "MA_SHARE_MODE_NOT_SUPPORTED";
    case MA_NO_BACKEND: return "MA_NO_BACKEND";
    case MA_NO_DEVICE: return "MA_NO_DEVICE";
    case MA_API_NOT_FOUND: return "MA_API_NOT_FOUND";
    case MA_INVALID_DEVICE_CONFIG: return "MA_INVALID_DEVICE_CONFIG";

        /* State errors. */
    case MA_DEVICE_BUSY: return "MA_DEVICE_BUSY";
    case MA_DEVICE_NOT_INITIALIZED: return "MA_DEVICE_NOT_INITIALIZED";
    case MA_DEVICE_NOT_STARTED: return "MA_DEVICE_NOT_STARTED";
    case MA_DEVICE_UNAVAILABLE: return "MA_DEVICE_UNAVAILABLE";

        /* Operation errors. */
    case MA_FAILED_TO_MAP_DEVICE_BUFFER: return "MA_FAILED_TO_MAP_DEVICE_BUFFER";
    case MA_FAILED_TO_UNMAP_DEVICE_BUFFER: return "MA_FAILED_TO_UNMAP_DEVICE_BUFFER";
    case MA_FAILED_TO_INIT_BACKEND: return "MA_FAILED_TO_INIT_BACKEND";
    case MA_FAILED_TO_READ_DATA_FROM_CLIENT: return "MA_FAILED_TO_READ_DATA_FROM_CLIENT";
    case MA_FAILED_TO_READ_DATA_FROM_DEVICE: return "MA_FAILED_TO_READ_DATA_FROM_DEVICE";
    case MA_FAILED_TO_SEND_DATA_TO_CLIENT: return "MA_FAILED_TO_SEND_DATA_TO_CLIENT";
    case MA_FAILED_TO_SEND_DATA_TO_DEVICE: return "MA_FAILED_TO_SEND_DATA_TO_DEVICE";
    case MA_FAILED_TO_OPEN_BACKEND_DEVICE: return "MA_FAILED_TO_OPEN_BACKEND_DEVICE";
    case MA_FAILED_TO_START_BACKEND_DEVICE: return "MA_FAILED_TO_START_BACKEND_DEVICE";
    case MA_FAILED_TO_STOP_BACKEND_DEVICE: return "MA_FAILED_TO_STOP_BACKEND_DEVICE";
    case MA_FAILED_TO_CONFIGURE_BACKEND_DEVICE: return "MA_FAILED_TO_CONFIGURE_BACKEND_DEVICE";
    case MA_FAILED_TO_CREATE_MUTEX: return "MA_FAILED_TO_CREATE_MUTEX";
    case MA_FAILED_TO_CREATE_EVENT: return "MA_FAILED_TO_CREATE_EVENT";
    case MA_FAILED_TO_CREATE_SEMAPHORE: return "MA_FAILED_TO_CREATE_SEMAPHORE";
    case MA_FAILED_TO_CREATE_THREAD: return "MA_FAILED_TO_CREATE_THREAD";
    default: return "Unknown";
    }
}

void AudioPlayer::playStream(const std::string &filePath)
{
    ma_decoder_config decoderConfig = ma_decoder_config_init(ma_format_unknown, 2, 0);
    decoderConfig.channelMap[0] = MA_CHANNEL_LEFT;
    decoderConfig.channelMap[1] = MA_CHANNEL_RIGHT;
    std::unique_ptr<ma_decoder> mp3Decoder = std::make_unique<ma_decoder>();
    ma_result result = ma_decoder_init_file_mp3(filePath.c_str(), &decoderConfig, mp3Decoder.get());
    if (result != MA_SUCCESS) {
        WARN << "Failed to init MP3 decoder for" << filePath << maErrorString(result);
        return;
    }

    sts_mixer_stream_t *stream = new sts_mixer_stream_t{};
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
    stream->sample.data = std::shared_ptr<uint8_t[]>(new uint8_t[DRMP3_SRC_CACHE_SIZE_IN_FRAMES * bytesPerFrame]);
    stream->sample.audiodata = stream->sample.data.get();

    stream->userdata = mp3Decoder.get();

    if (sts_mixer_play_stream(m_mixer.get(), stream, 0.5) < 0) {
        WARN << "unable to play sample, too many playing already";
        delete stream;
        return;
    }

    mp3Decoder.release();
}

AudioPlayer &AudioPlayer::instance()
{
    static AudioPlayer inst;
    return inst;
}
