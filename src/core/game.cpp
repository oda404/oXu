// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

static bool w_isClosed;

bool oxu::Game::w_init()
{
	/* Initialize SDL */
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		return false;
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	/* Create the window */
	window = SDL_CreateWindow(
	"oXu!", 						// window name
	SDL_WINDOWPOS_CENTERED, 		// window pos X
	SDL_WINDOWPOS_CENTERED,			// window pos Y
	1920, 1080, 0					// width, height, flags
	);

	if(!window)
	{
		return false;
	}

	w_isClosed = false;

	Cursor::getInstance().set();
	
	return true;
}

void oxu::Game::g_loop()
{
	SDL_Event w_event;

	graphicsHandler.init(window, &graphicsThread, &w_isClosed, &maxFPS);
	
	while(!w_isClosed)
	{
		/* Calculate delta time */
        startTick = SDL_GetTicks();
        deltaTime = (double)(startTick - lastTick) / 1000.0f;
        lastTick  = startTick;

		while(SDL_PollEvent(&w_event))
		{
			switch(w_event.type)
			{
				case SDL_QUIT:
					/* also breaks the graphics thread loop */
					w_isClosed = true;
					break;
			}
		}

		if(mapInfoI.hitCircles[mapInfoI.hitObjCapBottom].isFinished())
			++mapInfoI.hitObjCapBottom;

		/* check if should increment to next object */
		if(mapInfoI.timer.getEllapsedTimeAsMs() >= mapInfoI.hitCircles[mapInfoI.hitObjCapTop].getSpawnTime() - 450)
            ++mapInfoI.hitObjCapTop;

		/* Limit the FPS */
        if(1000 / maxFPS > SDL_GetTicks() - startTick)
        {
            SDL_Delay(1000 / maxFPS - SDL_GetTicks() + startTick);
        }
	}
	
	graphicsThread->join();
};

void oxu::Game::w_clean()
{
	/* destroy the window */
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	/* quit all SDL subsystems */
	SDL_Quit();
}
