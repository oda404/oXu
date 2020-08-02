// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

namespace oxu
{
	int Game::init()
	{
		thisThread = &Threads::instance().threads[MAIN_THREAD];
		thisThread->maxFPS = 1000;

		Logger::init();

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
		currentBeatmap = &songManager.getSong(1).getBeatmap(0);
		currentBeatmap->loadGenericInfo();
		currentBeatmap->loadGameInfo();

		/* Initiate the graphics handler */
		/* This spawns another thread */
		graphicsHandler.init(window, &windowState, &songManager);

		soundHandler.init();
		soundHandler.setMusicVolume(5);
		//TODO fix extra \r and the end of audiofilename
		soundHandler.loadMusic(songManager.getSong(1).path + '/' + songManager.getSong(1).getBeatmap(0).general.audioFilename);

		currentBeatmap->timer.start();

		soundHandler.playMusic(currentBeatmap->timer.getEllapsedTime());
		
		return true;
	}

	void Game::loop()
	{
		thisThread->timer.start();

		while(!windowState)
		{
			inputHandler.handleInput(windowState);

			std::unique_lock<std::mutex> inputLock(Threads::instance().mtx);

				if(currentBeatmap->hitObjects[currentBeatmap->objTopCap + 1].shouldBeAddedToPool(currentBeatmap->timer.getEllapsedTime()))
				{
					currentBeatmap->hitObjects[currentBeatmap->objTopCap + 1].errorMargin = currentBeatmap->timer.getEllapsedTime() - currentBeatmap->hitObjects[currentBeatmap->objTopCap + 1].getSpawnTime();
					++currentBeatmap->objTopCap;
				}

				if(currentBeatmap->hitObjects[currentBeatmap->objBotCap].shouldBeRemovedFromPool(currentBeatmap->timer.getEllapsedTime()))
				{
					++currentBeatmap->objBotCap;
				}
				
			inputLock.unlock();

			thisThread->calculateDelta();
			thisThread->limitFPS();
		}

		Threads::instance().threads[GRAPHICS_THREAD].thread->join();
	};

	void Game::clean()
	{
		if(StatusCodes::statusCode != StatusCodes::OK)
		{
			LOG_WARN("Exiting with return status {0}", StatusCodes::statusCode);
		}
		else
		{
			LOG_INFO("Exiting gracefully. Hai noroc!");
		}

		SDL_DestroyWindow(window);
		window = NULL;

		IMG_Quit();

		SDL_Quit();
	}
}
