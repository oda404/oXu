// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"sound.hpp"

namespace oxu
{
    SoundHandler::~SoundHandler()
    {
        Mix_PauseMusic();
        Mix_HaltMusic();

        Mix_FreeMusic(musicTrack);
        musicTrack = NULL;

        Mix_CloseAudio();
        Mix_Quit();
    }

    void SoundHandler::init(SongManager *songManager_p)
    {
        songManager = songManager_p;
        currentBeatmap = &songManager->getSong(0).getBeatmap(0);

        thisThread = &Threads::get(Threads::SOUND);
        thisThread->init([this]() -> bool {return initThread();}, 1000);

        while(!thisThread->doneInit);
    }

    bool SoundHandler::initSDL()
    {
        audioRate = 44100;
        audioFormat = AUDIO_S16SYS;
        audioChannels = 2;
        audioBuffers = 0;

        if(Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) < 0)
        {
            LOG_ERR(Mix_GetError());
            Status::code = Status::MIX_OPEN_FAIL;
            return false;
        }

        if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
        {
            LOG_ERR(Mix_GetError());
            Status::code = Status::MIX_INIT_FAIL;
            return false;
        }

        setSongVolume(25);

        return true;
    }

    bool SoundHandler::initThread()
    {
        if(!initSDL())
        {
            return false;
        }

        thisThread->doneInit = true;

        startThread();

        return true;
    }

    void SoundHandler::startThread()
    {
        while(true)
        {
            thisThread->calculateDelta();

            while(thisThread->pipeline.pollRequest(request))
            {
                switch(request.instruction)
                {
                case SOUND_LOAD_SONG:
                    loadSong();
                    break;

                case SOUND_PLAY_SONG:
                    playSongDelayed();
                    break;

                case SOUND_HALT_THREAD:
                    return;
                }
            }

            thisThread->limitFPS();
        }
    }

    void SoundHandler::loadSong()
    {
        Mix_FreeMusic(musicTrack);
        musicTrack = NULL;

        std::string temp = currentBeatmap->path.substr(0, currentBeatmap->path.find_last_of('/')) + '/' + currentBeatmap->general.audioFilename;

        temp = temp.substr(0, temp.size() - 1);

        musicTrack = Mix_LoadMUS(temp.c_str());

        if(!musicTrack)
        {
            LOG_ERR(Mix_GetError());
        }
    }

    void SoundHandler::playSongDelayed()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(currentBeatmap->startPaddingTime - currentBeatmap->timer.getEllapsedTimeMilli()));

        Mix_PlayMusic(musicTrack, 0);
        
        Mix_RewindMusic();
        Mix_SetMusicPosition((currentBeatmap->timer.getEllapsedTimeMilli() - currentBeatmap->startPaddingTime) / 1000.0);
    }

    void SoundHandler::setSongVolume(const uint8_t &volume)
    {
        Mix_VolumeMusic(volume * MIX_MAX_VOLUME / 100);
    }
}
