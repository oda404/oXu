// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"soundHandler.hpp"

oxu::SoundHandler::SoundHandler() { }

oxu::SoundHandler::~SoundHandler()
{
    Mix_FreeMusic(musicTrack);
    musicTrack = NULL;

    Mix_CloseAudio();
    Mix_Quit();
}

bool oxu::SoundHandler::init()
{
    audioRate     = 44100;
    audioFormat   = AUDIO_S32;
    audioChannels = 1;
    audioBuffers  = 4096;

    if(Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers < 0))
    {
        //log message
        return false;
    }

    if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        // log message
        return false;
    }

    return true;
}

bool oxu::SoundHandler::loadMusic(const char *fileName)
{
    Mix_FreeMusic(musicTrack);
    musicTrack = NULL;

    musicTrack = Mix_LoadMUS(fileName);

    if(!musicTrack)
    {
        return false;
    }

    return true;
}

void oxu::SoundHandler::playMusic()
{
    Mix_PlayMusic(musicTrack, 0);
}

void oxu::SoundHandler::setVolume(const int &volume)
{
    Mix_VolumeMusic(volume);
}