#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<filesystem>
#include<string>

#include<oXu/utils/logger.hpp>
#include<oXu/skin/config.hpp>

namespace oxu
{
    class Skin
    {
    private:
        std::string path;
        std::string name;

        SDL_Texture **textures;
        bool texturesAreAllocated = false;

        SDL_Cursor *customCursor = NULL;

        void parseAndLoadTexture(const std::string &path, SDL_Renderer *targetRenderer);

    public:
        Skin(const std::string &path_p, const std::string &name_p);

        ~Skin();

        SDL_Texture *getTexture(uint8_t texEnum);

        void setCursor();

        void loadTextures(SDL_Renderer *renderer);

        void unloadTextures();
    };
}