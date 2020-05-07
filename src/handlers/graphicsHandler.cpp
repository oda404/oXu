// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphicsHandler.hpp"

oxu::GraphicsHandler::GraphicsHandler() { }

bool oxu::GraphicsHandler::init(SDL_Window *window, std::shared_ptr<std::thread> *gThreadSource, bool *w_statePtr)
{
    doneInit = false;

    /* pointer to check if the window is open from the graphics thread */
    w_isClosed = w_statePtr;

    /* Set the window ptr */
    this->window = window;

    /* get the current context */
    context = SDL_GL_GetCurrentContext();

    /* initiate the playfield */
    mapInfoI.playField.init(Vector2<int>(1920, 1080)); // stupid hardcoded screen size

    /* Create the thread */
    *gThreadSource = std::make_shared<std::thread>([this]{render();});

    /* Wait for the new thread to finish initiating
    to avoid any context problems */
    while(!doneInit);

    return true;
}

oxu::GraphicsHandler::~GraphicsHandler()
{
    SDL_DestroyRenderer(w_renderer);
    w_renderer = NULL;

    SDL_GL_DeleteContext(context);
}

void oxu::GraphicsHandler::render()
{
    /* make the current context from the new thread */
    SDL_GL_MakeCurrent(window, context);

    /* Enable texture batching */
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

    /* create the renderer */
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /* Initiate the textures here because they need the renderer */
    texturesI.init(w_renderer);

    doneInit = true;

    mapManagerI.enumBeatMaps();
    mapManagerI.loadHitObjects(0);
    mapManagerI.loadMapInfo(0);

    mapInfoI.timer.start();

    /* delta time calculation stuff */
    uint32_t startTick;
    uint32_t lastTick   = 0;
    double   deltaTime  = 0.0;

    /* the render loop */
    while(!*w_isClosed)
    {
        /* Calculate delta time */
        startTick = SDL_GetTicks();
        deltaTime = (double)(startTick - lastTick) / 1000.0f;
        lastTick  = startTick;

        /* Start rendering */
        SDL_RenderClear(w_renderer);
        
        /* need to implemenet some bounds */
        for(int16_t i = mapInfoI.hitObjCapTop; i >=  mapInfoI.hitObjCapBottom; --i)
        {
            if(mapInfoI.hitCircles[i].getSpawnTime() - mapInfoI.ARInSeconds <= mapInfoI.timer.getEllapsedTimeAsMs())
            {   
                /* This shouldn't render the textures now, but batch them together
                for the GPU to draw when SDL_RenderPresent is called */
                SDL_RenderCopy(w_renderer, texturesI.gameTextures[0], NULL, mapInfoI.hitCircles[i].getHCSDLRect()); // hit circle
                SDL_RenderCopy(w_renderer, texturesI.gameTextures[2], NULL, mapInfoI.hitCircles[i].getHCSDLRect()); // hit circle overlay
                SDL_RenderCopy(w_renderer, texturesI.gameTextures[1], NULL, mapInfoI.hitCircles[i].getACSDLRect()); // approach circle

                if(!mapInfoI.hitCircles[i].approachCircle(deltaTime))
                    ++mapInfoI.hitObjCapBottom;
            }
        }

        SDL_RenderPresent(w_renderer);
        
        /* Limit the FPS */
        if(1000 / maxFPS > SDL_GetTicks() - startTick)
        {
            SDL_Delay(1000 / maxFPS - SDL_GetTicks() + startTick);
        }
    }
}
