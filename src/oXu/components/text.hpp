#pragma once

#include<string>

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_ttf.h>

namespace oxu
{
    struct TextBox
    {
        SDL_Texture *tex = NULL;
        std::string text;
        SDL_Rect rect;

        void createTexture(SDL_Renderer *targetRanderer, TTF_Font *font);

        ~TextBox();
    };
}