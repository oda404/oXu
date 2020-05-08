// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_mixer.h>

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

	public:
		SoundHandler();

		~SoundHandler();

		bool init();

		bool loadMusic(const char *filePath);

		void playMusic();

		void setVolume(const int &volume);
	};
}