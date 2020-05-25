// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<experimental/filesystem>
#include<vector>
#include<string>

#include<oXu/utils/vector2.hpp>
#include<oXu/utils/logger.hpp>

namespace fs = std::experimental::filesystem;

namespace oxu
{
    struct Textures
    {
    private:
        Textures();

        std::vector<SDL_Surface*>   gameSurfaces;
        std::vector<SDL_Texture*>   gameTextures;

        /* Used for combining multiple digits together */
        std::vector<SDL_Texture*>   extraComboNumTex;

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

        void loadSkinSurfaces(const std::string &skinPath);

        void createTextures(SDL_Renderer *renderer);

        /* Surface getters */
        inline SDL_Surface *getHCSurf() { return gameSurfaces[0]; }

        inline SDL_Surface *getACSurf() { return gameSurfaces[1]; }

        inline SDL_Surface *getComboNumDefaultSurf() { return gameSurfaces[3]; }

        /* Texture getters */
        inline SDL_Texture *getHCTex() { return gameTextures[0]; }

        inline SDL_Texture *getACTex() { return gameTextures[1]; }

        inline SDL_Texture *getHCOverlayTex() { return gameTextures[2]; }

        SDL_Texture *getComboNumTex(SDL_Renderer *renderer, const uint8_t &n);

    };
}
