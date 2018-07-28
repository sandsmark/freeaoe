#pragma once

#include <memory>
#include <mutex>

struct sts_mixer_t;
struct mal_device;

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    void playSound(const int id, const int civilization);

    static AudioPlayer &instance();

private:
    void playSample(unsigned char *data, size_t size, const float pan = 0.f);

    static uint32_t malCallback(mal_device *device, uint32_t frameCount, void *buffer);

    std::unique_ptr<sts_mixer_t> m_mixer;
    std::unique_ptr<mal_device> m_device;
    std::mutex m_mutex;
};

