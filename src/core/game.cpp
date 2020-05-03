// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

bool oxu::Game::w_init()
{
	/* Initialize SDL */
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
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

	Cursor::getInstance().set();

	return true;
}

void oxu::Game::g_loop()
{
	SDL_Event w_event;

	GameComponents::getInstance().gameTimer.start();

	/* Initiates the handlers
	which also creates the renderer thread */
	graphicsHandler.init(window);
	
	while(!w_isClosed)
	{
		while(SDL_PollEvent(&w_event))
		{
			switch(w_event.type)
			{
				case SDL_QUIT:
					w_isClosed = true;
					break;
			}
		}
	}
};

void oxu::Game::w_clean()
{
	/* destroy the window */
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	/* quit SDL video subsystem */
	SDL_Quit();
}
