#include"textures.hpp"

oxu::Textures &oxu::Textures::getInstance()
{
    static Textures instance;
    return instance;
}

oxu::Textures::Textures() { }

oxu::Textures::~Textures()
{
    /* Destroy all game textures */
    for(SDL_Texture *tex: gameTextures)
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
}

void oxu::Textures::init(SDL_Renderer *w_renderer)
{   
    /* Good ol' yandere dev oriented programming */

    /* TODO: implement actual individual skins */
    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/hitcircle.png") );
    if(!gameTextures[0])
    {
        LOG_WARN("{0}", IMG_GetError());
    }
    gameTexturesSizes.emplace_back(Vector2<int>());
    SDL_QueryTexture(gameTextures[0], NULL, NULL, &gameTexturesSizes[0][0], &gameTexturesSizes[0][1]);

    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/approachcircle.png") );
    if(!gameTextures[1])
    {
        LOG_WARN("{0}", IMG_GetError());
    }
    gameTexturesSizes.emplace_back(Vector2<int>());
    SDL_QueryTexture(gameTextures[1], NULL, NULL, &gameTexturesSizes[1][0], &gameTexturesSizes[1][1]);

    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/hitcircleoverlay.png") );
    if(!gameTextures[2])
    {
        LOG_WARN("{0}", IMG_GetError());
    }
    // Uses the same texture size as the hit circle
}
