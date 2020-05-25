// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"soundHandler.hpp"

oxu::SoundHandler::~SoundHandler()
{
    /* Halt all channels i think */
    Mix_HaltChannel(-1);
    /* Free all allocated channels */
    Mix_AllocateChannels(0);

    /* Mix and halt the music */
    Mix_PauseMusic();
    Mix_HaltMusic();

    /* Free the music */
    Mix_FreeMusic(musicTrack);
    musicTrack = NULL;

    /* Free the chunks */
    Mix_FreeChunk(hitSound);
    hitSound = NULL;
    
    Mix_CloseAudio();
    Mix_Quit();
}

bool oxu::SoundHandler::init(BeatmapManager *beatmapManagerPtr)
{
    beatmapManager = beatmapManagerPtr;

    audioRate     = 44100;
    audioFormat   = AUDIO_S16SYS;
    audioChannels = 2;
    audioBuffers  = 0;

    if(Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) < 0)
    {
        LOG_ERR("Failed to open audio: {0}", Mix_GetError());
        return false;
    }

    if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        LOG_ERR("Failed to initialize Mixer: {0}", Mix_GetError());
        return false;
    }

    Mix_AllocateChannels(10);

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

bool oxu::SoundHandler::loadSoundEffects(const std::string &skinPath)
{
    hitSound = Mix_LoadWAV( (skinPath + "/normal-hitnormal.wav").c_str() );
    if(!hitSound)
    {
        LOG_WARN("Couldn't load sound effect: {0}", Mix_GetError());
        return false;
    }

    return true;
}

void oxu::SoundHandler::playMusic()
{
    beatmapManager->getObjectsInfo().timer.restart();
    Mix_PlayMusic(musicTrack, 0);
    beatmapManager->getObjectsInfo().timer.start();
}

void oxu::SoundHandler::playHitSound()
{
    Mix_PlayChannel(-1, hitSound, 0);
}

void oxu::SoundHandler::setMusicVolume(const int &volume)
{
    Mix_VolumeMusic(volume);
}

void oxu::SoundHandler::setEffectsVolume(const int &volume)
{
    Mix_VolumeChunk(hitSound, volume);
}
