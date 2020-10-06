// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "oXu.hpp"

#include<oXu/core/status.hpp>
#include<oXu/core/scaling.hpp>
#include<oXu/core/dirs.hpp>
#include<oXu/utils/logger.hpp>

#include<oXu/core/threading/threadsManager.hpp>

#include<oXu/skin/skinManager.hpp>
#include<oXu/beatmap/songManager.hpp>

namespace oxu
{
	static Thread *thisThread;
	SkinManager skinManager;
	SongManager songManager;

	oXu::~oXu()
	{
		ThreadsManager::get(Threads::GRAPHICS).pipeline.makeRequest(Graphics::HALT_THREAD);
		ThreadsManager::get(Threads::GRAPHICS).join();

		if(Status::code != Status::OK)
		{
			OXU_LOG_WARN("Exiting with return status {0}", Status::code);
		}
		else
		{
			OXU_LOG_INFO("Exiting gracefully. Hai noroc!");
		}

		SDL_DestroyWindow(window);
		window = NULL;

		SDL_Quit();
	}

	bool oXu::init()
	{
		thisThread = &ThreadsManager::get(Threads::MAIN);
		thisThread->setMaxFPS(1000);

		Scaling::screenSize = { 1920, 1080 };
		Scaling::oxuPx = Scaling::screenSize.y / 480.f;

		Logger::init();
		Dirs::setDirs();

		if( SDL_Init(SDL_INIT_VIDEO) != 0 )
		{
			OXU_LOG_ERR(SDL_GetError());
			Status::code = Status::SDL_INIT_FAIL;
			return false;
		}

		window = SDL_CreateWindow(
			"oXu!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			Scaling::screenSize.x,
			Scaling::screenSize.y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);

		if(!window)
		{
			OXU_LOG_ERR(SDL_GetError());
			Status::code = Status::WINDOW_CREATE_FAIL;
			return false;
		}

		graphicsHandler.init(window, &songManager, &skinManager);

		songManager.enumerateSongs();
		songManager.setCurrentSong(0);
		songManager.setCurrentBeatmap(0);
		songManager.getCurrentBeatmap()->loadGenericInfo();
		songManager.getCurrentBeatmap()->loadGameInfo();

		return true;
	}

	void oXu::update()
	{
		thisThread->start();
		songManager.getCurrentBeatmap()->start();
		while(!windowState)
		{
			thisThread->limitFPS();

			songManager.getCurrentBeatmap()->updateObjects(thisThread->getDelta());
			
			inputHandler.handleInput(windowState);
		}
	};
}
