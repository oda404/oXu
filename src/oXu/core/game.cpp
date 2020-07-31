// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

bool oxu::Game::windowState = false;

int oxu::Game::init()
{
	/* Initiate the logger */
	Logger::init();

	/* Initialize SDL */
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		LOG_ERR(SDL_GetError());
		StatusCodes::statusCode = StatusCodes::SDL_INIT_FAIL;
		return false;
	}

	if( IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 )
	{
		LOG_ERR(IMG_GetError());
		StatusCodes::statusCode = StatusCodes::IMG_INIT_FAIL;
		return false;
	}

	Scaling::screenSize = { 1920, 1080 };
	Scaling::oxuPx = Scaling::screenSize.y / 480.f;

	/* Create the window */
	window = SDL_CreateWindow(
		"oXu!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Scaling::screenSize.x,
		Scaling::screenSize.y,
		0
	);

	if(!window)
	{
		LOG_ERR(SDL_GetError());
		StatusCodes::statusCode = StatusCodes::WINDOW_CREATE_FAIL;
		return false;
	}

	songManager.enumerateSongs();
	songManager.getSong(1).getBeatmap(0).loadGenericInfo();
	songManager.getSong(1).getBeatmap(0).loadGameInfo();
	
	/* Enumerate all skins */
	skinManager.enumSkins();

	/* Load the skins images onto surfaces */
	Textures::getInstance().loadSkinSurfaces(skinManager.getSkinPath(0));

	/* Set the cursor png */
	cursor.set(skinManager.getSkinPath(0));

	/* Initiate the graphics handler */
	/* This spawns another thread */
	graphicsHandler.init(window, &graphicsThread, &deltaTime, &windowState, &songManager);

	soundHandler.init();
	soundHandler.setMusicVolume(5);
	//TODO fix extra \r and the end of audiofilename
	soundHandler.loadMusic(songManager.getSong(1).path + '/' + songManager.getSong(1).getBeatmap(0).general.audioFilename);

	songManager.getSong(1).getBeatmap(0).timer.start();

	soundHandler.playMusic(songManager.getSong(1).getBeatmap(0).timer.getEllapsedTimeAsMs());
	
	return true;
}

void oxu::Game::loop()
{
	Beatmap &beatmap = songManager.getSong(1).getBeatmap(0);

	while(!windowState)
	{
		calculateDeltaTime();

		inputHandler.handleInput(windowState);

		if(beatmap.hitObjects[beatmap.objTopCap + 1].shouldBeAddedToPool(beatmap.timer.getEllapsedTimeAsMs()))
		{
			beatmap.hitObjects[beatmap.objTopCap + 1].errorMargin = beatmap.timer.getEllapsedTimeAsMs() - beatmap.hitObjects[beatmap.objTopCap + 1].getSpawnTime();
			++beatmap.objTopCap;
		}

		if(beatmap.hitObjects[beatmap.objBotCap].shouldBeRemovedFromPool(beatmap.timer.getEllapsedTimeAsMs()))
		{
			++beatmap.objBotCap;
		}

		limitFPS();
	}
	
	graphicsThread->join();
};

void oxu::Game::clean()
{
	if(StatusCodes::statusCode != StatusCodes::OK)
	{
		LOG_WARN("Exiting with return status {0}", StatusCodes::statusCode);
	}
	else
	{
		LOG_INFO("Exiting gracefully. Hai noroc!");
	}

	/* destroy the window */
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();

	/* quit all SDL subsystems */
	SDL_Quit();
}

void oxu::Game::calculateDeltaTime()
{
	lastTick  = startTick;
	startTick = SDL_GetTicks();
	deltaTime = (startTick - lastTick) / 1000.0;
}

void oxu::Game::limitFPS()
{
	if(1000.0 / maxFPS > SDL_GetTicks() - startTick)
	{
		SDL_Delay(1000.0 / maxFPS - SDL_GetTicks() + startTick);
	}
}
