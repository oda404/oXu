// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_mixer.h>

#include"../utils/logger.hpp"
#include"../beatmap/mapInfo.hpp"

#include<cstdint>

namespace oxu
{
	class SoundHandler
	{
	private:
		int     audioRate;
		int16_t audioFormat;
		int     audioChannels;
		int     audioBuffers;

		Mix_Music *musicTrack = NULL;

		// ====== effect sounds ======
		Mix_Chunk *hitSound   = NULL;

	public:
		SoundHandler();
		~SoundHandler();

		bool init();

		bool loadMusic(const char *filePath);

		bool loadSoundEffects();

		void playMusic();

		void playHitSound();

		void setMusicVolume(const int &volume);

		void setEffectsVolume(const int &volume);

	};
}