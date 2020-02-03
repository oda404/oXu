#pragma once
#include<SFML/Graphics.hpp>
#include"../3rdParty/bass.h"

namespace oxu
{
	class SoundHandler
	{
	private:
		HSTREAM streamHandle;
		sf::Clock audioPlayingOffset;
	public:
		SoundHandler()
		{
			BASS_Init(-1, 44100, 0, 0, NULL);
			BASS_SetVolume(0.3f);
		}

		void setAudioVolume(const float &volume)
		{
			BASS_SetVolume(volume);
		}

		void loadAudioFile(const void *audioName)
		{
			streamHandle = BASS_StreamCreateFile(FALSE, audioName, 0, 0, 0);
		}

		void playAudio()
		{
			BASS_ChannelPlay(streamHandle, FALSE);
			audioPlayingOffset.restart();
		}

		void freeAudio()
		{
			BASS_Free();
		}

		sf::Int32 getAudioPlayingOffset()
		{
			return audioPlayingOffset.getElapsedTime().asMilliseconds();
		}

	};
}