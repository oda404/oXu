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

    /* Enable texture batching */
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

    texturesI.init(w_renderer);

    gcI.playField.init(Vector2i(1920, 1080)); // stupid hardcoded screen size

    return true;
}

oxu::GraphicsHandler::~GraphicsHandler()
{
    SDL_DestroyRenderer(w_renderer);
    w_renderer = NULL;

	IMG_Quit();
}

void oxu::GraphicsHandler::render(const double &dt)
{
    SDL_RenderClear(w_renderer);
    
    /* need to implemenet some bounds */
    for(int i = gcI.hitCircles.size() - 1; i >= 0 ; --i)
    {
        if(gcI.hitCircles[i].getSpawnTime() - 0.450f <= gcI.gameTimer.getEllapsedTimeAsMs())
        {   
            /* This shouldn't render the textures now, but batch them together
            for the GPU to draw when SDL_RenderPresent is called */
            SDL_RenderCopy(w_renderer, texturesI.gameTextures[0], NULL, gcI.hitCircles[i].getHCSDLRect()); // hit circle
            SDL_RenderCopy(w_renderer, texturesI.gameTextures[2], NULL, gcI.hitCircles[i].getHCSDLRect()); // hit circle overlay
            SDL_RenderCopy(w_renderer, texturesI.gameTextures[1], NULL, gcI.hitCircles[i].getACSDLRect()); // approach circle

            gcI.hitCircles[i].approachCircle(dt);
        }
    }

    SDL_RenderPresent(w_renderer);
}
