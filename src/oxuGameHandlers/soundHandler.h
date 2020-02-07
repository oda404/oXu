#pragma once
#include<SFML/Graphics.hpp>
#include"../3rdParty/bass.h"

#include<memory>

namespace oxu
{
	class SoundHandler
	{
	private:
		HSTREAM streamHandle;
		std::shared_ptr<sf::Clock> audioPlayingOffset;
	public:
		SoundHandler()
		{
			BASS_Init(-1, 44100, 0, 0, NULL);
			BASS_SetVolume(0.0f);
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
			audioPlayingOffset = std::make_shared<sf::Clock>();
		}

		void freeAudio()
		{
			BASS_StreamFree(streamHandle);
			BASS_Free();
		}

		sf::Int32 getAudioPlayingOffset()
		{
			return audioPlayingOffset->getElapsedTime().asMilliseconds();
		}

		void handleSound(const std::uint8_t &sceneID)
		{
			static bool go = true;

			switch(sceneID)
			{
				case 0:
					
					break;

				case 1:
					if(go)
					{
						loadAudioFile("yomi.mp3");
						playAudio();
						go= false;
					}
					break;
			}
		}

	};
}