// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"soundHandler.hpp"

oxu::SoundHandler::SoundHandler()
{
    BASS_Init(-1, 44100, 0, 0, NULL);
    initialVolume = BASS_GetVolume();
    BASS_SetVolume(0.2f);
}

void oxu::SoundHandler::setVolumeToDefault() { BASS_SetVolume(initialVolume); }

void oxu::SoundHandler::setAudioVolume(const float &volume) { BASS_SetVolume(volume); }

void oxu::SoundHandler::loadAudioFile(const void *audioName) { streamHandle = BASS_StreamCreateFile(FALSE, audioName, 0, 0, 0); }

void oxu::SoundHandler::playAudio() 
{
    BASS_ChannelPlay(streamHandle, 0);
    mapTimer.start();
}

void oxu::SoundHandler::freeAudio()
{
    BASS_StreamFree(streamHandle);
    BASS_Free();
}

void oxu::SoundHandler::pauseAudio()
{
    bytePositionAtPause = BASS_ChannelGetPosition(streamHandle, BASS_POS_BYTE);
    BASS_ChannelPause(streamHandle);
    mapTimer.pause();
}

void oxu::SoundHandler::resumeAudio()
{
    BASS_ChannelPlay(streamHandle, 0);
    BASS_ChannelSetPosition(streamHandle, bytePositionAtPause, BASS_POS_BYTE);
    mapTimer.resume();
}

int64_t oxu::SoundHandler::getAudioPlayingOffset()
{
    return mapTimer.getEllapsedTimeAsMs();
}

void oxu::SoundHandler::scrollVolume(const float &delta) { BASS_SetVolume(BASS_GetVolume() + delta / 100); }
