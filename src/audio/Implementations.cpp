#define DR_MP3_IMPLEMENTATION
#include <miniaudio/extras/dr_mp3.h>

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_JACK
#define MA_NO_SDL
#define MA_NO_OPENAL

// the miniaudio pulseaudio backend is broken, so fall back to the pulseaudio alsa emulation for now
//#define MA_NO_ALSA

#define MA_NO_PULSEAUDIO
//#define ma_DEBUG_OUTPUT
#include <miniaudio/miniaudio.h>
