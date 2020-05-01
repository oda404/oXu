// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

unsigned int windowWidth = 640, windowHeight = 480;

bool oxu::Game::w_init()
{
	/* Initialize SDL */
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{

		return false;
	}

	/* Create the window */
	window = SDL_CreateWindow(
	"oXu!", 						// window name
	SDL_WINDOWPOS_CENTERED, 		// window pos X
	SDL_WINDOWPOS_CENTERED,			// window pos Y
	1920, 1080, 0	// width, height, flags
	);

	if(!window)
	{
		return false;
	}

	if(!sceneManager.init(window))
	{
		return false;
	}

	Cursor::getInstance().set();

	return true;
}

void oxu::Game::g_loop()
{
	SDL_Event w_event;

	MapManager m;

	m.loadHitObjects("songs/Imperial Circus Dead Decadence - Yomi yori Kikoyu, Koukoku no Tou to Honoo no Shoujo. (DoKito) [Kyouaku].osu");

	GameComponents::getInstance().gameTimer.start();

	uint32_t lastTick = 0;
	double deltaTime = 0.0;
	
	while(!w_isClosed)
	{
		uint32_t startTick = SDL_GetTicks();
		deltaTime = (double)(startTick - lastTick) / 1000.0f;
		lastTick = startTick;

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

		sceneManager.handleCurrentSceneGraphics(deltaTime);

		/* Limit the fps to whatever is the max */
		if(1000 / maxFPS > SDL_GetTicks() - startTick)
		{
			SDL_Delay(1000 / maxFPS - SDL_GetTicks() + startTick);
		}
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
