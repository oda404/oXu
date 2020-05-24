// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

bool oxu::Game::w_isClosed = false;

oxu::Game &oxu::Game::getInstance()
{
	static Game instance;
	return instance;
}

bool oxu::Game::init()
{
	/* Initiate the logger */
	Logger::init();

	/* Initialize SDL */
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		LOG_ERR("{0}", SDL_GetError());
		return false;
	}

	if( IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 )
	{
		LOG_ERR("{0}", IMG_GetError());
		return false;
	}

	Global::screenSize = { 1920, 1080 };
	Global::oxuPx = Global::screenSize.getY() / 480.f;

	/* Create the window */
	window = SDL_CreateWindow(
	"oXu!",                      // window name
	SDL_WINDOWPOS_CENTERED,      // window pos X
	SDL_WINDOWPOS_CENTERED,      // window pos Y
	Global::screenSize.getX(),   // screen width
	Global::screenSize.getY(),   // screen height
	0                            // flags
	);

	if(!window)
	{
		LOG_ERR("Failed to create the window: {0}", SDL_GetError());
		return false;
	}
	
	/* Enumerate all skins */
	skinsManager.enumSkins();

	/* Load the skins images onto surfaces */
	Textures::getInstance().loadSkinSurfaces(skinsManager.getSkinPath(0));

	/* Set the cursor png */
	Cursor::getInstance().set(skinsManager.getSkinPath(0));

	/* Enumerate all the beatmaps */
	beatmapManager.enumBeatMaps();
	/* Load info/objects from song 0 map 0 */
	beatmapManager.loadMapInfo(0, 0);
	beatmapManager.loadHitObjects(0, 0);

	/* Initiate the graphics handler */
	graphicsHandler.init(window, &graphicsThread, &w_isClosed);

	/* Initiate the sound handler */
	soundHandler.init();

	soundHandler.loadMusic((beatmapManager.getSongPath(0) + '/' + mapInfoI.getGeneralAttr("AudioFilename")).c_str());
	soundHandler.setMusicVolume(5);
	
	soundHandler.loadSoundEffects(skinsManager.getSkinPath(0));
	soundHandler.setEffectsVolume(5);

	soundHandler.playMusic();

	/* Initiate the input handler */
	inputHandler.init(&soundHandler);
	
	return true;
}

void oxu::Game::loop()
{
	while(!w_isClosed)
	{
		calculateDeltaTime();

		/* event/input handling */
		inputHandler.handleInput(w_isClosed);

		if(mapInfoI.hitCircles[mapInfoI.hitObjCapBottom].isDone())
		{
			soundHandler.playHitSound();
			++mapInfoI.hitObjCapBottom;
		}

		/* check if should increment to next object */
		if(mapInfoI.timer.getEllapsedTimeAsMs() >= mapInfoI.hitCircles[mapInfoI.hitObjCapTop].getHitTime() - 450)
		    ++mapInfoI.hitObjCapTop;

		limitFPS();
	}
	
	graphicsThread->join();
};

void oxu::Game::clean()
{
	LOG_INFO("Exiting gracefully. Hai noroc!");
	/* destroy the window */
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	/* quit all SDL subsystems */
	SDL_Quit();
}

void oxu::Game::calculateDeltaTime()
{
	startTick = SDL_GetTicks();
	deltaTime = (double)(startTick - lastTick) / 1000.0f;
	lastTick  = startTick;
}

void oxu::Game::limitFPS()
{
	if(1000 / maxFPS > SDL_GetTicks() - startTick)
	{
		SDL_Delay(1000 / maxFPS - SDL_GetTicks() + startTick);
	}
}
