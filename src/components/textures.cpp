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
    SDL_QueryTexture(gameTextures[0], NULL, NULL, &HCHalfTex, NULL);
    HCHalfTex /= 2;

    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/approachcircle.png") );
    SDL_QueryTexture(gameTextures[1], NULL, NULL, &ACHalfTex, NULL);
    ACHalfTex /= 2;

    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/hitcircleoverlay.png") );
    // uses the same rect as the hitcircle
}

int &oxu::Textures::getHCHalfTex()
{
    return HCHalfTex;
}

int &oxu::Textures::getACHalfTex()
{
    return ACHalfTex;
}
