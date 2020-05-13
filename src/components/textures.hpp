// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<experimental/filesystem>
#include<vector>
#include<string>

#include"../utils/vector2.hpp"
#include"../utils/logger.hpp"

namespace fs = std::experimental::filesystem;

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
        Textures(const Textures&)            = delete;

        /* Disable move-ctor */
        Textures(Textures&&)                 = delete;

        Textures& operator=(const Textures&) = delete;

        Textures& operator=(Textures&&)      = delete;

        ~Textures();

        std::vector<SDL_Surface*>   gameSurfaces;
        std::vector<SDL_Texture*>   gameTextures;

        void loadSkinTextures(const std::string &skinPath);

        void createTextures(SDL_Renderer *renderer);
    };
}
