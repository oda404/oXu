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
    // Set the texture filter to be linear
    // Basically scales the texture more nicely
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    /* Good ol' yandere dev oriented programming */

    /* TODO: implement actual individual skins */
    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/hitcircle.png") );
    gameTexturesSizes.emplace_back(Vector2i());
    SDL_QueryTexture(gameTextures[0], NULL, NULL, &gameTexturesSizes[0].x, &gameTexturesSizes[0].y);

    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/approachcircle.png") );
    gameTexturesSizes.emplace_back(Vector2i());
    SDL_QueryTexture(gameTextures[1], NULL, NULL, &gameTexturesSizes[1].x, &gameTexturesSizes[1].y);

    gameTextures.emplace_back( IMG_LoadTexture(w_renderer, "skins/hitcircleoverlay.png") );
    // Uses the same texture size as the hit circle
}
