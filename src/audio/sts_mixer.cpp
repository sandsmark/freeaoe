/*
  sts_mixer.h - v0.01
  written 2016 by Sebastian Steinhauer

  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>
*/

#include "sts_mixer.h"

#include <algorithm>

enum {
  STS_MIXER_VOICE_STOPPED,
  STS_MIXER_VOICE_PLAYING,
  STS_MIXER_VOICE_STREAMING
};


static float sts_mixer__clamp_sample(const float sample) {
  return std::clamp(sample, -1.f, 1.f);
}


static float sts_mixer__get_sample(sts_mixer_sample_t* sample, unsigned int position) {
  switch (sample->audio_format) {
    case STS_MIXER_SAMPLE_FORMAT_8:
      return (float)((int8_t*)sample->audiodata)[position] / 127.0f;
    case STS_MIXER_SAMPLE_FORMAT_16:
      return (float)((int16_t*)sample->audiodata)[position] / 32767.0f;
    case STS_MIXER_SAMPLE_FORMAT_32:
      return (float)((int32_t*)sample->audiodata)[position] / 2147483647.0f;
    case STS_MIXER_SAMPLE_FORMAT_FLOAT:
      return ((float*)sample->audiodata)[position];
    default:
      return 0.0f;
  }
}


static void sts_mixer__reset_voice(sts_mixer_t* mixer, const int i) {
  sts_mixer_voice_t*  voice = &mixer->voices[i];
  voice->state = STS_MIXER_VOICE_STOPPED;
  if (voice->stream && voice->stream->stop_callback) {
    voice->stream->stop_callback(i, &voice->stream->sample, voice->stream->userdata);
  }
  delete voice->sample;
  delete voice->stream;
  voice->sample = nullptr;
  voice->stream = nullptr;
  voice->position = voice->gain = voice->pitch = voice->pan = 0.0f;
}


static int sts_mixer__find_free_voice(sts_mixer_t* mixer) {
  int i;

  for (i = 0; i < STS_MIXER_VOICES; ++i) {
      if (mixer->voices[i].state == STS_MIXER_VOICE_STOPPED) { return i; }
  }
  return -1;
}


void sts_mixer_init(sts_mixer_t* mixer, unsigned int frequency, int audio_format) {
  int i;

  for (i = 0; i < STS_MIXER_VOICES; ++i) { sts_mixer__reset_voice(mixer, i); }
  mixer->frequency = frequency;
  mixer->gain = 1.0f;
  mixer->audio_format = audio_format;
}


void sts_mixer_shutdown(sts_mixer_t* mixer) {
  sts_mixer_init(mixer, 0, 0);
}


int sts_mixer_get_active_voices(sts_mixer_t* mixer) {
  int   i, active;
  for (i = 0, active = 0; i < STS_MIXER_VOICES; ++i) {
    if (mixer->voices[i].state != STS_MIXER_VOICE_STOPPED) { ++active; }
  }
  return active;
}


int sts_mixer_play_sample(sts_mixer_t* mixer, sts_mixer_sample_t* sample, float gain, float pitch, float pan) {
  int                 i;
  sts_mixer_voice_t*  voice;

  i = sts_mixer__find_free_voice(mixer);
  if (i >= 0) {
    voice = &mixer->voices[i];
    voice->gain = gain;
    voice->pitch = std::clamp(pitch, 0.1f, 10.0f);
    voice->pan = std::clamp(pan * 0.5f, -0.5f, 0.5f);
    voice->position = 0.0f;
    delete voice->sample;
    voice->sample = sample;
    voice->stream = nullptr;
    voice->state = STS_MIXER_VOICE_PLAYING;
  }
  return i;
}


int sts_mixer_play_stream(sts_mixer_t* mixer, sts_mixer_stream_t* stream, float gain) {
  int                 i;
  sts_mixer_voice_t*  voice;

  i = sts_mixer__find_free_voice(mixer);
  if (i >= 0) {
    voice = &mixer->voices[i];
    voice->gain = gain;
    voice->position = 0.0f;
    delete voice->sample;
    voice->sample = nullptr;
    voice->stream = stream;
    voice->state = STS_MIXER_VOICE_STREAMING;
  }
  return i;
}


void sts_mixer_stop_voice(sts_mixer_t* mixer, int voice) {
  if (voice >= 0 && voice < STS_MIXER_VOICES) { sts_mixer__reset_voice(mixer, voice); }
}


void sts_mixer_stop_sample(sts_mixer_t* mixer, sts_mixer_sample_t* sample) {
  int i;

  for (i = 0; i < STS_MIXER_VOICES; ++i) {
    if (mixer->voices[i].sample == sample) { sts_mixer__reset_voice(mixer, i); }
  }
}


void sts_mixer_stop_stream(sts_mixer_t* mixer, sts_mixer_stream_t* stream) {
  int i;

  for (i = 0; i < STS_MIXER_VOICES; ++i) {
    if (mixer->voices[i].stream == stream) { sts_mixer__reset_voice(mixer, i); }
  }
}


void sts_mixer_mix_audio(sts_mixer_t* mixer, void* output, unsigned int samples) {
  sts_mixer_voice_t*  voice;
  unsigned int        i, position;
  float               left, right, advance, sample;
  int8_t*             out_8 = (int8_t*)output;
  int16_t*            out_16 = (int16_t*)output;
  int32_t*            out_32 = (int32_t*)output;
  float*              out_float = (float*)output;

  // mix all voices
  advance = 1.0f / (float)mixer->frequency;
  for (; samples > 0; --samples) {
    left = right = 0.0f;
    for (i = 0; i < STS_MIXER_VOICES; ++i) {
      voice = &mixer->voices[i];
      if (voice->state == STS_MIXER_VOICE_PLAYING) {
        position = (int)voice->position;
        if (position < voice->sample->length) {
          sample = sts_mixer__clamp_sample(sts_mixer__get_sample(voice->sample, position) * voice->gain);
          left += sts_mixer__clamp_sample(sample * (0.5f - voice->pan));
          right += sts_mixer__clamp_sample(sample * (0.5f + voice->pan));
          voice->position += (float)voice->sample->frequency * advance * voice->pitch;
        } else { sts_mixer__reset_voice(mixer, i); }
      } else if (voice->state == STS_MIXER_VOICE_STREAMING) {
        position = ((int)voice->position) * 2;
        if (position >= voice->stream->sample.length) {
          // buffer empty...refill
          voice->stream->callback(&voice->stream->sample, voice->stream->userdata);
          voice->position = 0.0f;
          position = 0;
        }
        if (voice->stream->sample.length > 0) {
          left += sts_mixer__clamp_sample(sts_mixer__get_sample(&voice->stream->sample, position) * voice->gain);
          right += sts_mixer__clamp_sample(sts_mixer__get_sample(&voice->stream->sample, position + 1) * voice->gain);
          voice->position += (float)voice->stream->sample.frequency * advance;
        } else {
          sts_mixer__reset_voice(mixer, i);
        }
      }
    }

    // write to buffer
    left = sts_mixer__clamp_sample(left);
    right = sts_mixer__clamp_sample(right);
    switch (mixer->audio_format) {
      case STS_MIXER_SAMPLE_FORMAT_8:
        *out_8++ = (char)(left * 127.0f);
        *out_8++ = (char)(right * 127.0f);
        break;
      case STS_MIXER_SAMPLE_FORMAT_16:
        *out_16++ = (int16_t)(left * 32767.0f);
        *out_16++ = (int16_t)(right * 32767.0f);
        break;
      case STS_MIXER_SAMPLE_FORMAT_32:
        *out_32++ = (int32_t)(left * 2147483647.0f);
        *out_32++ = (int32_t)(right * 2147483647.0f);
        break;
      case STS_MIXER_SAMPLE_FORMAT_FLOAT:
        *out_float++ = left;
        *out_float++ = right;
        break;
    }
  }
}
