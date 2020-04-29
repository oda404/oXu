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
    SDL_QueryTexture(gameTextures[0], NULL, NULL, &HCHalfTex, NULL);
    HCHalfTex /= 2;

    gameTextures.push_back( IMG_LoadTexture(w_renderer, "skins/approachcircle.png") );
    ACHalfTex /= 2;
    SDL_QueryTexture(gameTextures[1], NULL, NULL, &ACHalfTex, NULL);
}

SDL_Texture *oxu::Textures::getHCTex()
{
    return gameTextures[0];
}

SDL_Texture *oxu::Textures::getACTex()
{
    return gameTextures[1];
}

int &oxu::Textures::getHCHalfTex()
{
    return HCHalfTex;
}

int &oxu::Textures::getACHalfTex()
{
    return ACHalfTex;
}
