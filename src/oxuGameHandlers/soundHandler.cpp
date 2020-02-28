#include"soundHandler.hpp"

oxu::SoundHandler::SoundHandler()
{
    BASS_Init(-1, 44100, 0, 0, NULL);
    initialVolume = BASS_GetVolume();
    BASS_SetVolume(0.2f);
}

void oxu::SoundHandler::setVolumeToDefault() { BASS_SetVolume(initialVolume); }

void oxu::SoundHandler::setAudioVolume(const float &volume) { BASS_SetVolume(volume); }

void oxu::SoundHandler::loadAudioFile(const void *audioName) { streamHandle = BASS_StreamCreateFile(FALSE, audioName, 0, 0, 0); }

void oxu::SoundHandler::playAudio() 
{
    BASS_ChannelPlay(streamHandle, FALSE);
    audioPlayingOffset = std::make_shared<sf::Clock>();
}

void oxu::SoundHandler::freeAudio()
{
    BASS_StreamFree(streamHandle);
    BASS_Free();
}

sf::Int32 oxu::SoundHandler::getAudioPlayingOffset() const { return audioPlayingOffset->getElapsedTime().asMilliseconds(); }

void oxu::SoundHandler::scrollVolume(const float &delta) { BASS_SetVolume(BASS_GetVolume() + delta / 100); }