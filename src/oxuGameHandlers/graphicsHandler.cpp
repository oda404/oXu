// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphicsHandler.hpp"

oxu::GraphicsHandler::GraphicsHandler() { }

bool oxu::GraphicsHandler::init(SDL_Window *window)
{
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    w_renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
    if(!w_renderer)
    {
        return false;
    }

    texturesI.init(w_renderer);

    gameComponentsI.cursor.init();

    return true;
}

oxu::GraphicsHandler::~GraphicsHandler()
{
    SDL_DestroyRenderer(w_renderer);
    w_renderer = NULL;

	IMG_Quit();
}

void oxu::GraphicsHandler::render()
{
    SDL_RenderClear(w_renderer);
    
    SDL_RenderCopy(w_renderer, texturesI.getHCTex(), NULL, gameComponentsI.hitCircles[0].getSDLRect());

    SDL_RenderPresent(w_renderer);
}
