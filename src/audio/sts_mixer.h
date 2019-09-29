///////////////////////////////////////////////////////////////////////////////
// sts_mixer.h - v0.01
// written 2016 by Sebastian Steinhauer
//
//  LICENSE
//    Public domain. See "unlicense" statement at the end of this file.
//
//  ABOUT
//    A simple stereo audio mixer which is capable of mixing samples and audio streams.
//    Samples can be played with different gain, pitch and panning.
//    Streams can be played with different gain.
//    This library has no malloc/free. All structs have to be "prepared" by the user. So you can enroll your own memory management.
//    You have to implement/provide a real audio-backend to hear something from the speakers.
//    A good starting point would be SDL2 where you can use an audio callback to feed the audio device.
//
//  USAGE
//    Please note that most audio systems will run in a separate thread. So you have to take care about locking before modifying the sts_mixer_t state.
//    See the example at the end of the file.
//
//  VERSION HISTORY
//    0.01 (2016-05-01) initial version
//
#pragma once

#include <stdint.h>
#include <memory>

// The number of concurrent voices (channels) which are used to mix the audio.
// If you need more, use a higher number by setting #define STS_MIXER_VOICE n before including this header.
#ifndef STS_MIXER_VOICES
#define STS_MIXER_VOICES      32
#endif // STS_MIXER_VOICES

// Defines the various audio formats. Note that they are all on system endianess.
enum {
  STS_MIXER_SAMPLE_FORMAT_NONE,               // no format
  STS_MIXER_SAMPLE_FORMAT_8,                  // signed 8-bit
  STS_MIXER_SAMPLE_FORMAT_16,                 // signed 16-bit
  STS_MIXER_SAMPLE_FORMAT_32,                 // signed 32-bit
  STS_MIXER_SAMPLE_FORMAT_FLOAT               // floats
};


////////////////////////////////////////////////////////////////////////////////
//
//  SAMPLES
//
// A sample is a *MONO* piece of audio which is loaded fully to memory.
// It can be played with various gains, pitches and pannings.
//
struct sts_mixer_sample_t {
  unsigned int              length;           // length in samples (so 1024 samples of STS_MIXER_SAMPLE_FORMAT_16 would be 2048 bytes)
  unsigned int              frequency;        // frequency of this sample (e.g. 44100, 22000 ...)
  int                       audio_format;     // one of STS_MIXER_SAMPLE_FORMAT_*
  std::shared_ptr<uint8_t[]>  data;             // pointer to the wav data
  unsigned char             *audiodata;       // pointer to the actual audio data
};


////////////////////////////////////////////////////////////////////////////////
//
//  STREAMS
//
// A stream is *STEREO* audio which will be decoded/loaded as needed.
// It can be played with various gains. No panning or pitching.
//

// The callback which will be called when the stream needs more data.
typedef void (*sts_mixer_stream_callback)(sts_mixer_sample_t* sample, void* userdata);

typedef struct {
  void*                     userdata;         // a userdata pointer which will passed to the callback
  sts_mixer_stream_callback callback;         // this callback will be called when the stream needs more data
  sts_mixer_sample_t        sample;           // the current stream "sample" which holds the current piece of audio
} sts_mixer_stream_t;


////////////////////////////////////////////////////////////////////////////////
//
//  VOICES
//
// A voice is an audio source which will be used during mixing.
// It can play nothing, a sample or a stream.
// Most of those fields are considered "private" and you should not play around with those.
//
struct sts_mixer_voice_t {
  int                       state;
  sts_mixer_sample_t*       sample = nullptr;
  sts_mixer_stream_t*       stream = nullptr;
  float                     position;
  float                     gain;
  float                     pitch;
  float                     pan;
};


////////////////////////////////////////////////////////////////////////////////
//
//  MIXER
//
// The mixer state.
//
struct sts_mixer_t {
  float                     gain;             // the global gain (you can change it if you want to change to overall volume)
  unsigned int              frequency;        // the frequency for the output of mixed audio data
  int                       audio_format;     // the audio format for the output of mixed audio data
  sts_mixer_voice_t         voices[STS_MIXER_VOICES]{}; // holding all audio voices for this state
};


////////////////////////////////////////////////////////////////////////////////
//
//  API
//

// "Initializes" a new sts_mixer state.
void sts_mixer_init(sts_mixer_t* mixer, unsigned int frequency, int audio_format);
// "Shutdown" the mixer state. It will simply reset all fields.
void sts_mixer_shutdown(sts_mixer_t* mixer);

// Return the number of active voices. Active voices are voices that play either a stream or a sample.
int sts_mixer_get_active_voices(sts_mixer_t* mixer);

// Play the given sample with the gain, pitch and panning.
// Panning can be something between -1.0f (fully left) ...  +1.0f (fully right)
// Please note that pitch will be clamped so it cannot reach 0.0f (would be useless).
// Returns the number of the voice where this sample will be played or -1 if no voice was free.
int sts_mixer_play_sample(sts_mixer_t* mixer, sts_mixer_sample_t* sample, float gain, float pitch, float pan);

// Plays the given stream with the gain.
// Returns the number of the voice where this stream will be played or -1 if no voice was free.
int sts_mixer_play_stream(sts_mixer_t* mixer, sts_mixer_stream_t* stream, float gain);

// Stops voice with the given voice no. You can pass the returned number of sts_mixer_play_sample / sts_mixer_play_stream here.
void sts_mixer_stop_voice(sts_mixer_t* mixer, int voice);

// Stops all voices playing the given sample. Useful when you want to delete the sample and make sure it is not used anymore.
void sts_mixer_stop_sample(sts_mixer_t* mixer, sts_mixer_sample_t* sample);

// Stops all voices playing the given stream. Useful when you want to delete the stream and make sure it is not used anymore.
void sts_mixer_stop_stream(sts_mixer_t* mixer, sts_mixer_stream_t* stream);

// The mixing function. You should call the function if you need to pass more audio data to the audio device.
// Typically this function is called in a separate thread or something like that.
// It will write audio data in the specified format and frequency of the mixer state.
void sts_mixer_mix_audio(sts_mixer_t* mixer, void* output, unsigned int samples);
