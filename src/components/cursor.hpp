
#pragma once

#include<SDL2/SDL_mouse.h>
#include<SDL2/SDL_image.h>

#include"../utils/logger.hpp"

namespace oxu
{
    class Cursor
    {
    private:
        Cursor();
        SDL_Cursor *customCursor = NULL;

    public:
        ~Cursor();

        static Cursor &getInstance();

        /* Disable copy-ctor */
        Cursor(Cursor const&) = delete;

        /* Disable move-ctor */
        Cursor(Cursor&&) = delete;

        /* Loads whatever png named "cursor.png"
        exists in the skins folder as the cursor */
        void set();
    };
}