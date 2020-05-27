// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_mixer.h>

#include<cstdint>

#include<oXu/utils/logger.hpp>

#include<oXu/beatmap/beatmapManager.hpp>

namespace oxu
{
	class SoundHandler
	{
	private:
		BeatmapManager *beatmapManager;

		int       audioRate;
		int16_t   audioFormat;
		int       audioChannels;
		int       audioBuffers;

		Mix_Music *musicTrack = NULL;

		// ====== effect sounds ======
		Mix_Chunk *hitSound   = NULL;

	public:
		~SoundHandler();

		bool init(BeatmapManager *beatmapManagerPtr);

		bool loadMusic(const char *filePath);

		/* loads sound effects from the specified skin */
		bool loadSoundEffects(const std::string &skinPath);

		void playMusic();

		void playHitSound();

		void setMusicVolume(const int &volume);

		void setEffectsVolume(const int &volume);

	};
}