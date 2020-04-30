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

    gcI.cursor.init();
    gcI.playField.init(Vector2i(640, 480));

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

    static int currentObj = 0;
    
    for(int i = gcI.hitCircles.size() - 1; i >= 0 ; --i)
    {
        if(gcI.hitCircles[i].getSpawnTime() <= gcI.gameTimer.getEllapsedTimeAsMs())
        {     
            SDL_RenderCopy(w_renderer, texturesI.gameTextures[0], NULL, gcI.hitCircles[i].getHCSDLRect()); // hit circle
            SDL_RenderCopy(w_renderer, texturesI.gameTextures[2], NULL, gcI.hitCircles[i].getHCSDLRect()); // hit circle overlay
            SDL_RenderCopy(w_renderer, texturesI.gameTextures[1], NULL, gcI.hitCircles[i].getACSDLRect()); // approach circle
        }
    }

    SDL_RenderPresent(w_renderer);
}
