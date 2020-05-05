#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<vector>

#include"../utils/vector2.hpp"

namespace oxu
{
    struct Textures
    {
    private:
        Textures();

    public:
        /* Singleton stuff */
        static Textures &getInstance();

        /* Disable copy-ctor */
        Textures(const Textures&) = delete;

        /* Disable move-ctor */
        Textures(Textures&&) = delete;

        Textures& operator=(const Textures&) = delete;

        Textures& operator=(Textures&&) = delete;

        ~Textures();

        std::vector<SDL_Texture*>   gameTextures;
        std::vector<Vector2<int>>   gameTexturesSizes;

        void init(SDL_Renderer *w_renderer);
    };
}