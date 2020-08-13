// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_mixer.h>

#include<cstdint>
#include<string>

#include<oXu/utils/logger.hpp>

#include<oXu/core/threading/threads.hpp>
#include<oXu/core/status.hpp>

#include<oXu/beatmap/songManager.hpp>

namespace oxu
{
	class SoundHandler
	{
	private:
		int audioRate;
		int16_t audioFormat;
		int audioChannels;
		int audioBuffers;

		Mix_Music *musicTrack = NULL;

		Thread *thisThread;
		Request request;

		SongManager *songManager = NULL;
		Beatmap *currentBeatmap = NULL;

		bool initSDL();

		bool initThread();

		void startThread();

		void loadSong();

		void playSongDelayed();

		void setSongVolume(const uint8_t &volume);

	public:
		~SoundHandler();

		void init(SongManager *songManager_p);

	};
}
