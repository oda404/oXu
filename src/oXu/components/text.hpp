#pragma once

#include<string>

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_ttf.h>

#include<oXu/core/statusCodes.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    struct TextBox
    {
        SDL_Texture *tex = NULL;
        std::string text;
        SDL_Rect rect;

        ~TextBox();
    };

    class Text
    {
    public:
        TTF_Font *font = NULL;
        SDL_Texture *tex = NULL;

    public:
        bool init();

        void createTexture(SDL_Renderer *renderer, TextBox &textBox);

        ~Text();
    };
}