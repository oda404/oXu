#pragma once

#include<oXu/audio/sound.hpp>

namespace oxu
{
    class Player
    {
        ~Player();
        static void init();
        static void playSound(const Sound &sound_p);
    };
}