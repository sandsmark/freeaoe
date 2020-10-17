#define DR_MP3_IMPLEMENTATION
#include <miniaudio/extras/dr_mp3.h>

#ifndef __APPLE__
#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_JACK
#define MA_NO_SDL
#define MA_NO_OPENAL
#define MA_NO_ALSA
//#define ma_DEBUG_OUTPUT
#include <miniaudio/miniaudio.h>
#endif//__APPLE__
