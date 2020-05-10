// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphicsHandler.hpp"

oxu::GraphicsHandler::GraphicsHandler() { }

oxu::GraphicsHandler &oxu::GraphicsHandler::getInstance()
{
    static GraphicsHandler instance;
    return instance;
}

bool oxu::GraphicsHandler::init(SDL_Window *window, std::shared_ptr<std::thread> *gThreadSource, bool *w_statePtr, unsigned int *pMaxFPS)
{
    doneInit = false;

    /* pointer to check if the window is open from the graphics thread */
    w_isClosed = w_statePtr;

    maxFPS = pMaxFPS;

    /* Set the window ptr */
    this->window = window;

    /* get the current context */
    context = SDL_GL_GetCurrentContext();

    /* initiate the playfield */
    mapInfoI.playField.init(Vector2<int>(1920, 1080)); // stupid hardcoded screen size

    /* Create the thread */
    *gThreadSource = std::make_shared<std::thread>( [this] { render(); } );

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

#include"soundHandler.hpp"

void oxu::GraphicsHandler::render()
{
    /* make the current context from the new thread */
    SDL_GL_MakeCurrent(window, context);
 
    /* Enable texture batching */
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

    // Set the texture filter to be linear
    // Basically scales the texture more nicely
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    /* create the renderer */
    w_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!w_renderer)
    {
        LOG_ERR("Failed to create renderer: {0}", SDL_GetError());
    }

    /* Initiate the textures here because they need the renderer */
    texturesI.init(w_renderer);

    /* Initiate the mapMager */
    mapManagerI.enumBeatMaps();

    /* Load beat map info */
    mapManagerI.loadMapInfo(0);
    mapManagerI.loadHitObjects(0);

	SoundHandler::getInstance().init();
	SoundHandler::getInstance().setVolume(20);
	SoundHandler::getInstance().loadMusic(("songs/" + mapInfoI.mapGeneral.find("AudioFilename")->second).c_str());
	SoundHandler::getInstance().playMusic();

    mapInfoI.timer.start();

    doneInit = true;

    /* delta time calculation stuff */
    uint32_t startTick;
    uint32_t lastTick   = 0;
    double   deltaTime  = 0.0;

    int16_t i;

    /* the render loop */
    while(!*w_isClosed)
    {
        /* Calculate delta time */
        startTick = SDL_GetTicks();
        deltaTime = (double)(startTick - lastTick) / 1000.0f;
        lastTick  = startTick;

        /* Start rendering */
        SDL_RenderClear(w_renderer);

        for(i = mapInfoI.hitObjCapTop; i >=  mapInfoI.hitObjCapBottom; --i)
        {
            if(mapInfoI.timer.getEllapsedTimeAsMs() >= mapInfoI.hitCircles[i].getSpawnTime() - 450) // hardcoded val
            {   
                /* This shouldn't render the textures now, but batch them together
                for the GPU to draw when SDL_RenderPresent is called */
                SDL_RenderCopy(w_renderer, texturesI.gameTextures[0], NULL, mapInfoI.hitCircles[i].getHCSDLRect()); // hit circle
                SDL_RenderCopy(w_renderer, texturesI.gameTextures[2], NULL, mapInfoI.hitCircles[i].getHCSDLRect()); // hit circle overlay
                SDL_RenderCopy(w_renderer, texturesI.gameTextures[1], NULL, mapInfoI.hitCircles[i].getACSDLRect()); // approach circle
                
                /* if the circle is done approaching increment the bottom cap */
                mapInfoI.hitCircles[i].approachCircle(deltaTime);
            }   
        }

        SDL_RenderPresent(w_renderer);
        
        /* Limit the FPS */
        if(1000 / *maxFPS > SDL_GetTicks() - startTick)
        {
            SDL_Delay(1000 / *maxFPS - SDL_GetTicks() + startTick);
        }
    }
}
