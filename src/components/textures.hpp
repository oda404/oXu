#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<vector>

namespace oxu
{
    struct Textures
    {
    private:
        Textures();

        /* Assume that the png is a perfect square
            probably going to bite me in the ass later */
        int HCHalfTex;
        int ACHalfTex;

    public:
        /* Singleton stuff */
        static Textures &getInstance();

        /* Disable copy-ctor */
        Textures(Textures const&) = delete;

        /* Disable move-ctor */
        Textures(Textures&&) = delete;

        ~Textures();

        std::vector<SDL_Texture*> gameTextures;

        void init(SDL_Renderer *w_renderer);

        int &getHCHalfTex();
        int &getACHalfTex();
    };
}