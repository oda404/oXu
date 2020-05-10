// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_mixer.h>

#include"../utils/logger.hpp"

#include<cstdint>

namespace oxu
{
	class SoundHandler
	{
	private:
		SoundHandler();

		int     audioRate;
		int16_t audioFormat;
		int     audioChannels;
		int     audioBuffers;

		Mix_Music *musicTrack = NULL;

	public:
		~SoundHandler();

		/* =================== Singleton stuff ====================== */
		static SoundHandler &getInstance();

        SoundHandler(const SoundHandler&)            = delete;

        SoundHandler(SoundHandler&&)                 = delete;

        SoundHandler& operator=(const SoundHandler&) = delete;

        SoundHandler& operator=(SoundHandler&&)      = delete;
		/* ========================================================== */

		bool init();

		bool loadMusic(const char *filePath);

		void playMusic();

		void setVolume(const int &volume);
	};
}