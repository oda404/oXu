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

    gameComponentsI.cursor.init();

    return true;
}

oxu::GraphicsHandler::~GraphicsHandler()
{
    /* Destroy the renderer */
    SDL_DestroyRenderer(w_renderer);
	w_renderer = NULL;

	IMG_Quit();
}

void oxu::GraphicsHandler::render()
{
    SDL_RenderClear(w_renderer);

    SDL_RenderPresent(w_renderer);
}