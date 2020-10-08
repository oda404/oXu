// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include "oXu.hpp"

#include<oXu/core/status.hpp>
#include<oXu/core/scaling.hpp>
#include<oXu/core/dirs.hpp>
#include<oXu/core/threading/thread.hpp>
#include<oXu/utils/logger.hpp>

#include<oXu/skin/skinManager.hpp>
#include<oXu/beatmap/songManager.hpp>

#include<oXu/graphics/handler.hpp>
#include<oXu/audio/handler.hpp>
#include<oXu/input/handler.hpp>

namespace oxu
{
	static Thread c_selfThread;
	static SkinManager c_skinManager;
	static SongManager c_songManager;

	oXu::~oXu()
	{
		AudioHandler::shutDown();
		GraphicsHandler::shutDown();

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
		c_selfThread.setMaxFPS(1000);

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

		c_songManager.enumerateSongs();
		c_songManager.setCurrentSong(0);
		c_songManager.setCurrentBeatmap(0);
		c_songManager.getCurrentBeatmap()->loadGenericInfo();
		c_songManager.getCurrentBeatmap()->loadGameInfo();

		AudioHandler::init();
		GraphicsHandler::init(window, &c_songManager, &c_skinManager);

		return true;
	}

	void oXu::update()
	{
		c_selfThread.start();
		c_songManager.getCurrentBeatmap()->start();

		while(!windowState)
		{
			c_selfThread.limitFPS();

			c_songManager.getCurrentBeatmap()->updateObjects(c_selfThread.getDelta());
			
			InputHandler::handleInput(windowState);
		}
	};
}
