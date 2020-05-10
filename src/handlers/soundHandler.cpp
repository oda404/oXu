// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"soundHandler.hpp"

oxu::SoundHandler::SoundHandler() { }

oxu::SoundHandler::~SoundHandler()
{
    Mix_PauseMusic();

    Mix_FreeMusic(musicTrack);
    musicTrack = NULL;

    Mix_CloseAudio();
    Mix_Quit();
}

oxu::SoundHandler &oxu::SoundHandler::getInstance()
{
    static SoundHandler instance;
    return instance;
}

bool oxu::SoundHandler::init()
{
    audioRate     = 44100;
    audioFormat   = AUDIO_S32;
    audioChannels = 1;
    audioBuffers  = 4096;

    if(Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers < 0))
    {
        LOG_ERR("Failed to open audio: {0}", Mix_GetError());
        return false;
    }

    if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        LOG_ERR("Failed to initialize Mixer: {0}", Mix_GetError());
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
        LOG_ERR("Couldn't load music track: {0}", Mix_GetError());
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