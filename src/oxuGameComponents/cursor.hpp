
#pragma once

#include<SDL2/SDL_rect.h>   // for the SDL_Rect
#include<SDL2/SDL_render.h> // for the SDL_Texture

#include "../oxuUtils/log.hpp"
#include "../oxuUtils/vector2.hpp"

namespace oxu
{
    class Cursor
    {
    private:
        Log logUtil;

        SDL_Texture *cursorTex  = NULL;
        SDL_Rect    cursorRect;
        Vector2f    halfTex; // so the cursor can be position on it's center point

    public:
        Cursor();
        ~Cursor();

        /* declared void because if the initialization fails
        it's not a core component and doesn't stop the game (no return value needed) */
        void initTexture(SDL_Texture *p_cursorTexture);

        SDL_Texture *getTexture();

        const SDL_Rect *getRect();

        void updatePos(const Vector2i &newPos);
    };
}