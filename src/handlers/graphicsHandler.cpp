// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphicsHandler.hpp"

oxu::GraphicsHandler::GraphicsHandler() { }

void oxu::GraphicsHandler::init(SDL_Window *window, std::shared_ptr<std::thread> *gThreadSource, bool *w_statePtr)
{
    doneInit = false;

    this->window = window;

    w_isClosed = w_statePtr;

    /* get the current context */
    context = SDL_GL_GetCurrentContext();

    /* Create the thread */
    *gThreadSource = std::make_shared<std::thread>( [this] { render(); } );

    /* Wait for the new thread to finish initiating
    to avoid any context problems */
    while(!doneInit);
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
    SDL_SetHint("SDL_RENDER_BATCHING", "1");

    // Set the texture filter to be linear
    // Basically scales the texture more nicely
    SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "1");

    /* create the renderer */
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!w_renderer)
    {
        LOG_ERR("{0}", SDL_GetError());
    }

    texturesI.createTextures(w_renderer);

    doneInit = true;

    /* the render loop */
    while(!*w_isClosed)
    {
        calculateDeltaTime();

        /* Start rendering */
        SDL_RenderClear(w_renderer);

        renderHitCircles();

        SDL_RenderPresent(w_renderer);

        limitFPS();
    }
}

void oxu::GraphicsHandler::renderHitCircles()
{
    for(i = mapInfoI.hitObjCapTop; i >=  mapInfoI.hitObjCapBottom; --i)
    {
        if(mapInfoI.timer.getEllapsedTimeAsMs() >= mapInfoI.hitCircles[i].getHitTime() - mapInfoI.ARInSeconds * 1000)
        {   
            HitCircle &HC = mapInfoI.hitCircles[i];
            /* This shouldn't render the textures now, but batch them together
            for the GPU to draw when SDL_RenderPresent is called */

            /* Hit circle */
            SDL_RenderCopy(w_renderer, texturesI.getHCTex(), NULL, HC.getHCRect());

            /* Hit circle overlay */
            SDL_RenderCopy(w_renderer, texturesI.getHCOverlayTex(), NULL, HC.getHCRect());

            /* Approach circle */
            SDL_RenderCopy(w_renderer, texturesI.getACTex(), NULL, HC.getACRect());

            /* Combo */
            SDL_RenderCopy(w_renderer, texturesI.getComboNumTex(w_renderer, HC.getCombo()), NULL, HC.getComboRect());
            
            /* Close the approach circle */
            HC.approachCircle(deltaTime);
        }   
    }
}

void oxu::GraphicsHandler::calculateDeltaTime()
{
    /* Calculate delta time */
    startTick = SDL_GetTicks();
    deltaTime = (double)(startTick - lastTick) / 1000.0f;
    lastTick  = startTick;
}

void oxu::GraphicsHandler::limitFPS()
{
    /* Limit the FPS */
    if(1000 / maxFPS > SDL_GetTicks() - startTick)
    {
        SDL_Delay(1000 / maxFPS - SDL_GetTicks() + startTick);
    }
}
