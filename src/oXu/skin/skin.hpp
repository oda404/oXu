#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_mouse.h>

#include<string>

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

        void parseAndLoadTexture(const std::string &texturePath, SDL_Renderer *targetRenderer);

    public:
        Skin(const std::string &path_p);

        ~Skin();

        SDL_Texture *getTexture(uint8_t texEnum);

        void setCursor();

        void loadTextures(SDL_Renderer *renderer);

        void unloadTextures();
    };
}