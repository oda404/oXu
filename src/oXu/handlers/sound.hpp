// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_mixer.h>

#include<cstdint>
#include<string>

#include<oXu/utils/logger.hpp>

#include<oXu/core/status.hpp>

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

		Mix_Chunk *hitSound = NULL;

	public:
		~SoundHandler();

		bool init();

		bool loadMusic(const std::string &filePath);

		bool loadSoundEffects(const std::string &skinPath);

		void playMusic(const uint32_t &offset);

		void playHitSound();

		void setMusicVolume(const uint8_t &volume);

		void setEffectsVolume(const uint8_t &volume);

	};
}
