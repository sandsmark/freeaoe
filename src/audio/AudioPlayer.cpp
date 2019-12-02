#include "AudioPlayer.h"

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>

#include "core/Logger.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "sts_mixer.h"

#define DR_MP3_IMPLEMENTATION
#include <genie/dat/Sound.h>
#include <genie/dat/SoundItem.h>
#include <mini_al/extras/dr_mp3.h>
#include <stddef.h>

#define MINI_AL_IMPLEMENTATION
#define MAL_NO_DECODING
#define MAL_NO_JACK
#define MAL_NO_SDL
#define MAL_NO_OPENAL
#define MAL_NO_ALSA
//#define MAL_DEBUG_OUTPUT
#include <mini_al/mini_al.h>

uint32_t AudioPlayer::malCallback(mal_device *device, uint32_t frameCount, void *buffer)
{
    AudioPlayer *that = reinterpret_cast<AudioPlayer*>(device->pUserData);

    std::lock_guard<std::mutex> guard(that->m_mutex);
    sts_mixer_mix_audio(that->m_mixer.get(), buffer, frameCount);

    return frameCount;
}

AudioPlayer::AudioPlayer()
{
    m_mixer = std::make_unique<sts_mixer_t>();
    sts_mixer_init(m_mixer.get(), 44100, STS_MIXER_SAMPLE_FORMAT_16);

    mal_device_config config = mal_device_config_init_playback(
                mal_format_s16,
                2,
                44100,
                malCallback
                );

    m_device = std::make_unique<mal_device>();
    mal_result ret = mal_device_init(nullptr, mal_device_type_playback, nullptr, &config, this, m_device.get());
    if (ret != MAL_SUCCESS) {
        WARN << "Failed to open playback device" << ret;
        return;
    }

    if (mal_device_start(m_device.get()) != MAL_SUCCESS) {
        WARN << "Failed to start playback device.";
        mal_device_uninit(m_device.get());
        return;
    }
}

AudioPlayer::~AudioPlayer()
{
    mal_device_uninit(m_device.get());
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
        DVIADPCM = 0x11
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
    std::lock_guard<std::mutex> guard(m_mutex);

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

AudioPlayer &AudioPlayer::instance()
{
    static AudioPlayer inst;
    return inst;
}
