#pragma once

#include<oxu/audio/sound.hpp>

namespace oxu
{
    class Player
    {
        ~Player();
        static void init();
        static void playSound(const Sound &sound_p);
    };
}