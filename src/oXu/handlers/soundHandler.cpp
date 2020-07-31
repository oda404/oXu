// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"soundHandler.hpp"

namespace oxu
{
    static int getNormalizedVolume(const uint8_t &volume)
    {
        return volume * MIX_MAX_VOLUME / 100;
    }

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

    bool oxu::SoundHandler::init()
    {
        audioRate = 44100;
        audioFormat = AUDIO_S16SYS;
        audioChannels = 2;
        audioBuffers = 0;

        if(Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) < 0)
        {
            LOG_ERR(Mix_GetError());
            StatusCodes::statusCode = StatusCodes::MIX_OPEN_FAIL;
            return false;
        }

        if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
        {
            LOG_ERR(Mix_GetError());
            StatusCodes::statusCode = StatusCodes::MIX_INIT_FAIL;
            return false;
        }

        Mix_AllocateChannels(10);

        return true;
    }

    bool oxu::SoundHandler::loadMusic(const std::string &fileName)
    {
        Mix_FreeMusic(musicTrack);
        musicTrack = NULL;

        std::string temp = fileName;

        temp = temp.substr(0, temp.size() - 1);

        musicTrack = Mix_LoadMUS(temp.c_str());

        if(!musicTrack)
        {
            LOG_ERR(Mix_GetError());
            return false;
        }

        return true;
    }

    bool oxu::SoundHandler::loadSoundEffects(const std::string &skinPath)
    {
        hitSound = Mix_LoadWAV( (skinPath + "/normal-hitnormal.wav").c_str() );
        if(!hitSound)
        {
            LOG_WARN(Mix_GetError());
            return false;
        }

        return true;
    }

    void oxu::SoundHandler::playMusic(const uint32_t &offset)
    {
        Mix_PlayMusic(musicTrack, 0);
        Mix_SetMusicPosition(offset / 1000.f);
    }

    void oxu::SoundHandler::playHitSound()
    {
        Mix_PlayChannel(-1, hitSound, 0);
    }

    void oxu::SoundHandler::setMusicVolume(const uint8_t &volume)
    {
        Mix_VolumeMusic(getNormalizedVolume(volume));
    }

    void oxu::SoundHandler::setEffectsVolume(const uint8_t &volume)
    {
        Mix_VolumeChunk(hitSound, volume);
    }
}
