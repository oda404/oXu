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
}

void oxu::Textures::loadSkinTextures(const std::string &skinPath)
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
}

void oxu::Textures::createTextures(SDL_Renderer *renderer)
{
    gameTextures.emplace_back(SDL_CreateTextureFromSurface(renderer, gameSurfaces[0]));

    gameTextures.emplace_back(SDL_CreateTextureFromSurface(renderer, gameSurfaces[1]));

    gameTextures.emplace_back(SDL_CreateTextureFromSurface(renderer, gameSurfaces[2]));
}
