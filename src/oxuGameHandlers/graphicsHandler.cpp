// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphicsHandler.hpp"

oxu::GraphicsHandler::GraphicsHandler() { }

bool oxu::GraphicsHandler::init(SDL_Window *window)
{
     // Initiate the renderer
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!w_renderer)
    {
        logUtil.log(Log::ERROR, SDL_GetError());
        return false;
    }

    // Load the textures
    cursorTex = IMG_LoadTexture(w_renderer, "../skins/cursor.png");
    if(!cursorTex)
    {
        logUtil.log(Log::WARNING, SDL_GetError());
    }

    return true;
}

oxu::GraphicsHandler::~GraphicsHandler()
{
    /* Destroy the renderer */
    SDL_DestroyRenderer(w_renderer);
	w_renderer = NULL;

    /* Destroy all textures */
    SDL_DestroyTexture(cursorTex);
    cursorTex = NULL;

	IMG_Quit();
}

void oxu::GraphicsHandler::render()
{
    SDL_RenderClear(w_renderer);

    //SDL_RenderCopy(w_renderer, cursorTex, NULL, NULL);

    SDL_RenderPresent(w_renderer);
}