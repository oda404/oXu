// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

bool oxu::Game::w_init()
{
	/* Initialize SDL */
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		logUtil.log(Log::ERROR, SDL_GetError());
		return false;
	}

	/* Create the window */
	window = SDL_CreateWindow(
	"oXu!", 				// window name
	SDL_WINDOWPOS_CENTERED, // window pos X
	SDL_WINDOWPOS_CENTERED, // window pos Y
	1280, 720, 0 			// width, height, flags
	);

	if(!window)
	{
		logUtil.log(Log::ERROR, SDL_GetError());
		return false;
	}

	if(!sceneManager.init(window))
	{
		return false;
	}

	return true;
}

void oxu::Game::g_loop()
{
	SDL_Event w_event;

	while(!w_isClosed)
	{
		g_calculateDeltaTime();

		while(SDL_PollEvent(&w_event))
		{
			switch(w_event.type)
			{
				case SDL_QUIT:
					w_isClosed = true;
					break;
			}
		}

		sceneManager.handleCurrentSceneInput();

		sceneManager.handleCurrentSceneGraphics();

	}
};

void oxu::Game::w_clean()
{
	/* destroy the window */
	SDL_DestroyWindow(window);
	window = NULL;

	/* quit SDL video subsystem */
	SDL_Quit();
}

void oxu::Game::g_calculateDeltaTime()
{
	dt_last = dt_now;
	dt_now = SDL_GetPerformanceCounter();
	deltaTime = (double)((dt_now - dt_last) * 1000 / (double)SDL_GetPerformanceFrequency() );
}
