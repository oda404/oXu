#pragma once
#include<SFML/Graphics.hpp>
#include"../3rdParty/bass.h"

#include<memory>
#include<vector>
#include<functional>

namespace oxu
{
	class SoundHandler
	{
	private:
		HSTREAM streamHandle;
		std::shared_ptr<sf::Clock> audioPlayingOffset;
		float initialVolume;

		std::vector<std::function<void(const void *fileName)>> sceneSoundHandlers;
	public:
		SoundHandler()
		{
			BASS_Init(-1, 44100, 0, 0, NULL);
			initialVolume = BASS_GetVolume();
			BASS_SetVolume(0.2f);

			//=================================== sound handler for the main menu ===============================================
			sceneSoundHandlers.push_back([this](const void *fileName) -> void { return this->handleMainMenuSound(fileName); });

			//=================================== sound handler for the song select menu ========================================
			sceneSoundHandlers.push_back([this](const void *fileName) -> void { return this->handleSongSelectMenuSound(fileName); });

			//=================================== sound handler for the game =====================================================
			sceneSoundHandlers.push_back([this](const void *fileName) -> void { return this->handleGameSound(fileName); });
		}

		void setVolumeToDefault()
		{
			BASS_SetVolume(initialVolume);
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

		sf::Int32 getAudioPlayingOffset() const
		{
			return audioPlayingOffset->getElapsedTime().asMilliseconds();
		}

		void handleMainMenuSound(const void *fileName)
		{
			//empty for now
		}

		void handleSongSelectMenuSound(const void *fileName)
		{
			//emtpy for now
		}

		void handleGameSound(const void *fileName)
		{
			static bool play = true;

			if(play)
			{
				loadAudioFile(fileName);
				playAudio();
				play = false;
			}
		}

		void handleSound(const std::uint8_t &sceneID)
		{
			sceneSoundHandlers[sceneID]("yomi.mp3");
		}

	};
}