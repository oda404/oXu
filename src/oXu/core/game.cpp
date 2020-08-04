// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "game.hpp"

namespace oxu
{
	bool Game::initSDL()
	{
		Logger::init();

		if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
		{
			LOG_ERR(SDL_GetError());
			Status::code = Status::SDL_INIT_FAIL;
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
			Status::code = Status::WINDOW_CREATE_FAIL;
			return false;
		}

		return true;
	}

	bool Game::init()
	{
		thisThread = &Threading::threads[MAIN];
		thisThread->maxFPS = 1000;

		if(!initSDL())
		{
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

		soundHandler.playMusic(currentBeatmap->timer.getEllapsedTimeMilli());
		
		return true;
	}

	void Game::loop()
	{
		thisThread->timer.start();

		while(!windowState)
		{
			thisThread->calculateDelta();

			inputHandler.handleInput(windowState);

			std::unique_lock<std::mutex> inputLock(Threading::mtx);

				currentBeatmap->updateObjects(thisThread->delta);
				
			inputLock.unlock();

			thisThread->limitFPS();
		}

		Threading::threads[GRAPHICS].thread.join();
	};

	void Game::clean()
	{
		if(Status::code != Status::OK)
		{
			LOG_WARN("Exiting with return status {0}", Status::code);
		}
		else
		{
			LOG_INFO("Exiting gracefully. Hai noroc!");
		}

		SDL_DestroyWindow(window);
		window = NULL;

		SDL_Quit();
	}
}
