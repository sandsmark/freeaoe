#pragma once

#include "core/SignalEmitter.h"

#include <stdint.h>
#include <memory>
#include <mutex>
#include <unordered_map>

struct ma_device;
struct sts_mixer_t;
struct sts_mixer_sample_t;

class AudioPlayer : public SignalReceiver
{
public:
    enum StandardSound {
        TributeSound
    };

    AudioPlayer();
    ~AudioPlayer();

    void playSound(const StandardSound id, const float pan = 0.f, const float volume = 1.f);

    void playSound(const int id, const int civilization, const float pan = 0.f, const float volume = 1.f);
    void playStream(const std::string &filename);
    void stopStream(const std::string &filename);

    static AudioPlayer &instance();

    void onSoundVolumeChanged();
    void onMusicVolumeChanged();

private:
    void playSample(const std::shared_ptr<uint8_t[]> &data, const float pan = 0.f, const float volume = 1.f);

    static void malCallback(ma_device *device, void *buffer, const void *, uint32_t frameCount);
    static void mp3Callback(sts_mixer_sample_t *sample, void *userdata);
    static void mp3StopCallback(const int id, sts_mixer_sample_t *sample, void *userdata);

    std::unique_ptr<sts_mixer_t> m_mixer;
    std::unique_ptr<ma_device> m_device;
    std::unordered_map<std::string, int> m_activeStreams;
    std::mutex m_mutex;
};

