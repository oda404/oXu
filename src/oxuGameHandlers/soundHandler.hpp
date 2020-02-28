#pragma once
#include<SFML/System.hpp>
#include"../3rdParty/bass.h"

#include<memory>

namespace oxu
{
	class SoundHandler
	{
	private:
		HSTREAM streamHandle;
		std::shared_ptr<sf::Clock> audioPlayingOffset;
		float initialVolume;

	public:
		SoundHandler();

		void setVolumeToDefault();

		void setAudioVolume(const float &volume);

		void loadAudioFile(const void *audioName);

		void playAudio();

		void freeAudio();

		sf::Int32 getAudioPlayingOffset() const;

		static void scrollVolume(const float &delta);
	};
}