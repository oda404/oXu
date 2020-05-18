// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"textures.hpp"

char toChar(const uint8_t n)
{
    return (char)(n + 48);
}

oxu::Textures &oxu::Textures::getInstance()
{
    static Textures instance;
    return instance;
}

oxu::Textures::Textures() { }

oxu::Textures::~Textures()
{
    /* Destroy all game textures */
    for(SDL_Surface *surface: gameSurfaces)
    {
        SDL_FreeSurface(surface);
        surface = NULL;
    }

    for(SDL_Texture *tex: gameTextures)
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }

    for(SDL_Texture *tex: extraComboNumTex)
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
}

void oxu::Textures::loadSkinSurfaces(const std::string &skinPath)
{
    /* TODO: implement actual individual skins */
    gameSurfaces.emplace_back( IMG_Load( (skinPath + "/hitcircle.png").c_str() ) );
    if(!gameSurfaces[0])
    {
        LOG_WARN("{0}", IMG_GetError());
    }

    gameSurfaces.emplace_back( IMG_Load( (skinPath+ "/approachcircle.png").c_str() ) );
    if(!gameSurfaces[1])
    {
        LOG_WARN("{0}", IMG_GetError());
    }
    
    gameSurfaces.emplace_back( IMG_Load( (skinPath + "/hitcircleoverlay.png").c_str() ) );
    if(!gameSurfaces[2])
    {
        LOG_WARN("{0}", IMG_GetError());
    }

    /* Load default numbers surfaces */
    for(uint8_t i = 0; i < 10; ++i)
    {
        gameSurfaces.emplace_back( IMG_Load( (skinPath + "/default-" + toChar(i) + ".png").c_str() ) );
        if(!gameSurfaces[3 + i])
        {
            LOG_WARN("{0}", IMG_GetError());
        }
    }
}

void oxu::Textures::createTextures(SDL_Renderer *renderer)
{
    for(uint8_t i = 0; i < gameSurfaces.size(); ++i)
    {
        gameTextures.emplace_back(SDL_CreateTextureFromSurface(renderer, gameSurfaces[i]));
    }
}

SDL_Texture *oxu::Textures::getComboNumTex(SDL_Renderer *renderer, const uint8_t &n)
{
    if(n < 10)
    {
        return gameTextures[3 + n];
    }

    /* Only create new texture with the combined digits if it doesn't exist */
    if(n - 10 == extraComboNumTex.size())
    {
        /* Create a new surface which has the same attributes as the combo numbers surface (gamSurface[3]) used as default */
        SDL_Surface *s = SDL_CreateRGBSurface(gameSurfaces[3]->flags, gameSurfaces[3]->w * 2,
        gameSurfaces[3]->h, 32, gameSurfaces[3]->format->Rmask, gameSurfaces[3]->format->Gmask, 
        gameSurfaces[3]->format->Bmask, gameSurfaces[3]->format->Amask);

        /* Blit the first digit */
        SDL_BlitSurface(gameSurfaces[3 + n / 10], NULL, s, NULL);

        SDL_Rect destRec;
        destRec.x = gameSurfaces[3]->w;
        destRec.y = 0;
        destRec.w = gameSurfaces[3]->w;
        destRec.h = gameSurfaces[3]->h;

        /* Blit the second digit */
        SDL_BlitSurface(gameSurfaces[3 + n % 10], NULL, s, &destRec);

        extraComboNumTex.emplace_back(SDL_CreateTextureFromSurface(renderer, s));

        SDL_FreeSurface(s);
    }

    return extraComboNumTex[n - 10];
}
