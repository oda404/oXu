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
    for(int i = 0; i < gameTextures.size(); ++i)
    {
        SDL_DestroyTexture(gameTextures[i]);
        gameTextures[i] = NULL;
    }
}

void oxu::Textures::init(SDL_Renderer *w_renderer)
{
    /* Good ol' yandere dev oriented programming */

    /* TODO: implement actual individual skins */
    gameTextures.push_back( IMG_LoadTexture(w_renderer, "skins/hitcircle.png") );
    gameTextures.push_back( IMG_LoadTexture(w_renderer, "skins/approachcircle.png") );
}

SDL_Texture *oxu::Textures::getHCTex()
{
    return gameTextures[0];
}

SDL_Texture *oxu::Textures::getACTex()
{
    return gameTextures[1];
}