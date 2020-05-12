#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<vector>

#include"../utils/vector2.hpp"
#include"../utils/logger.hpp"

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

        std::vector<SDL_Surface*>   gameSurfaces;
        std::vector<SDL_Texture*>   gameTextures;

        void init();

        void createTextures(SDL_Renderer *renderer);
    };
}