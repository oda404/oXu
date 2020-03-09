// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include<SFML/System.hpp>
#include<bass.h>
#include"../oxuGameComponents/timer.hpp"

#include<memory>

namespace oxu
{
	class SoundHandler
	{
	private:
		HSTREAM streamHandle;
		QWORD bytePositionAtPause;
		Timer mapTimer;
		float initialVolume;

	public:
		SoundHandler();

		void setVolumeToDefault();

		void setAudioVolume(const float &volume);

		void loadAudioFile(const void *audioName);

		void playAudio();

		void freeAudio();

		void pauseAudio();

		void resumeAudio();

		int64_t getAudioPlayingOffset();

		static void scrollVolume(const float &delta);
	};
}
