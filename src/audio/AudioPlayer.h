#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <memory>
#include <mutex>

struct sts_mixer_t;
struct mal_device;

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    void playSample(unsigned char *data, size_t size, const float pan = 0.f);

    static AudioPlayer &instance();

private:
    static uint32_t malCallback(mal_device *device, uint32_t frameCount, void *buffer);

    std::unique_ptr<sts_mixer_t> m_mixer;
    std::unique_ptr<mal_device> m_device;
    std::mutex m_mutex;
};

#endif // AUDIOPLAYER_H
