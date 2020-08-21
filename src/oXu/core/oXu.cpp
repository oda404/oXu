// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "oXu.hpp"

#include<mutex>

#include<oXu/core/status.hpp>
#include<oXu/core/scaling.hpp>
#include<oXu/core/dirs.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
	oXu::~oXu()
	{
		Threads::get(Threads::GRAPHICS).pipeline.makeRequest(Request(GRAPHICS_HALT_THREAD));
		Threads::get(Threads::SOUND).pipeline.makeRequest(Request(SOUND_HALT_THREAD));

		Threads::get(Threads::MAIN).join();
		Threads::get(Threads::GRAPHICS).join();
		Threads::get(Threads::SOUND).join();

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

	bool oXu::initSDL()
	{
		Logger::init();

		if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
		{
			LOG_ERR(SDL_GetError());
			Status::code = Status::SDL_INIT_FAIL;
			return false;
		}

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

	bool oXu::init()
	{
		thisThread = &Threads::get(Threads::MAIN);
		thisThread->init([]() -> bool {return true;}, 1000);

		Scaling::screenSize = { 1920, 1080 };
		Scaling::oxuPx = Scaling::screenSize.y / 480.f;

		Dirs::setDirs();

		if(!initSDL())
		{
			return false;
		}

		songManager.enumerateSongs();

		currentBeatmap = &songManager.getSong(0).getBeatmap(0);

		currentBeatmap->loadGenericInfo();
		currentBeatmap->loadGameInfo();

		graphicsHandler.init(window, &songManager);
		audioHandler.init(&songManager);

		currentBeatmap->start();

		start();
		
		return true;
	}

	void oXu::start()
	{
		while(!windowState)
		{
			thisThread->calculateDelta();

			inputHandler.handleInput(windowState);

			std::unique_lock<std::mutex> inputLock(Threads::mtx);

				currentBeatmap->updateObjects(thisThread->getDelta());
				
			inputLock.unlock();

			thisThread->limitFPS();
		}
	};
}
