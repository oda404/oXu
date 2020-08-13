#pragma once

#include<cstdint>
#include<vector>
#include<string>

#define MAIN_HALT_THREAD 1

#define GRAPHICS_HALT_THREAD 2

#define SOUND_LOAD_SONG  3
#define SOUND_PLAY_SONG 4
#define SOUND_PAUSE_SONG 5
#define SOUND_RESET_SONG 6
#define SOUND_SET_VOLUME 7
#define SOUND_HALT_THREAD 8

namespace oxu
{
    struct Request
    {
    public:
        Request(
            std::uint8_t instruction_p
        );

        Request();

        std::uint8_t instruction;
    };
}
