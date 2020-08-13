// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphics.hpp"

namespace oxu
{
    void GraphicsHandler::init(SDL_Window *window, SongManager *songManager)
    {
        this->songManager = songManager;
        this->window = window;

        /* maybe redundant since I don't use the openGL context directly
        but i'm gonna leave it here just in case */
        context = SDL_GL_GetCurrentContext();
        
        thisThread = &Threads::get(Threads::GRAPHICS);
        thisThread->init([this]() -> bool {return initThread();}, 240);

        while(!thisThread->doneInit);
    }

    GraphicsHandler::~GraphicsHandler()
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        TTF_CloseFont(font);
        font = NULL;

        TTF_Quit();

        IMG_Quit();

        SDL_GL_DeleteContext(context);
    }

    bool GraphicsHandler::initSDL()
    {
        SDL_GL_MakeCurrent(window, context);
        SDL_SetHint("SDL_RENDER_BATCHING", "1");
        SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "1");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(!renderer)
        {
            LOG_ERR(SDL_GetError());
            Status::code = Status::RENDERER_CREATE_FAIL;
            return false;
        }

        if( IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 )
		{
			LOG_ERR(IMG_GetError());
			Status::code = Status::IMG_INIT_FAIL;
			return false;
		}

        if( TTF_Init() < 0 )
		{
			LOG_ERR(TTF_GetError());
			Status::code = Status::TTF_INIT_FAIL;
			return false;
		}

        font = TTF_OpenFont((Dirs::res + "/fonts/Hack-Regular.ttf").c_str(), 20);
        if(!font)
        {
            LOG_ERR(TTF_GetError());
			Status::code = Status::FONT_LOAD_FAIL;
			return false;
        }

        return true;
    }

    bool GraphicsHandler::initThread()
    {
        if(!initSDL())
        {
            return false;
        }

        skinManager.enumerateSkins();

        skin = &skinManager.getSkin(0);
        skin->loadTextures(renderer);
        skin->setCursor();

        beatmap = &songManager->getSong(0).getBeatmap(0);

        thisThread->doneInit = true;

        startThread();

        return true;
    }

    void GraphicsHandler::startThread()
    {
        while(true)
        {
            thisThread->calculateDelta();

            while(thisThread->pipeline.pollRequest(request))
            {
                switch(request.instruction)
                {
                    case GRAPHICS_HALT_THREAD:
                        return;
                }
            }
            
            SDL_RenderClear(renderer);
                        
            std::unique_lock<std::mutex> lockGuard(Threads::mtx);

                renderUI();
                renderHitCircles();

            lockGuard.unlock();

            SDL_RenderPresent(renderer);

            thisThread->limitFPS();
        }
    }

    void GraphicsHandler::renderHitCircles()
    {
        HitObject *obj;

        for(uint32_t i = beatmap->objBotCap; i < beatmap->objTopCap; ++i)
        {
            obj = &beatmap->hitObjects[i];

            SDL_RenderCopy(renderer, skin->getTexture(Tex::HIT_CIRCLE), NULL, obj->getHCRect());
            SDL_RenderCopy(renderer, skin->getTexture(Tex::APPROACH_CIRCLE), NULL, obj->getACRect());
            SDL_RenderCopy(renderer, skin->getTexture(Tex::HIT_CIRCLE_OVERLAY), NULL, obj->getHCRect());
        }
    }

    void GraphicsHandler::renderThreadsInfo()
    {
        static double renderTimer = 0.0;

        renderTimer += thisThread->getDelta();

        if(renderTimer >= 0.5)
        {
            renderTimer = 0.0;

            gameUI.graphicsThreadFPS.text = "Graphics: " + std::to_string(thisThread->FPS) + " FPS";
            gameUI.graphicsThreadFPS.createTexture(renderer, font);
            gameUI.graphicsThreadFPS.rect.x = Scaling::screenSize.x - gameUI.graphicsThreadFPS.rect.w - 10;
            gameUI.graphicsThreadFPS.rect.y = 10;

            gameUI.inputThreadFPS.text = "Input: " + std::to_string(Threads::get(Threads::MAIN).FPS) + " FPS";
            gameUI.inputThreadFPS.createTexture(renderer, font);
            gameUI.inputThreadFPS.rect.x = Scaling::screenSize.x - gameUI.inputThreadFPS.rect.w - 10;
            gameUI.inputThreadFPS.rect.y = gameUI.graphicsThreadFPS.rect.y + gameUI.graphicsThreadFPS.rect.h + 10;

            gameUI.soundThreadFPS.text = "Sound: " + std::to_string(Threads::get(Threads::SOUND).FPS) + " FPS";
            gameUI.soundThreadFPS.createTexture(renderer, font);
            gameUI.soundThreadFPS.rect.x = Scaling::screenSize.x - gameUI.soundThreadFPS.rect.w - 10;
            gameUI.soundThreadFPS.rect.y = gameUI.inputThreadFPS.rect.y + gameUI.inputThreadFPS.rect.h + 10;
        }

        SDL_RenderCopy(renderer, gameUI.graphicsThreadFPS.tex, NULL, &gameUI.graphicsThreadFPS.rect);
        SDL_RenderCopy(renderer, gameUI.inputThreadFPS.tex, NULL, &gameUI.inputThreadFPS.rect);
        SDL_RenderCopy(renderer, gameUI.soundThreadFPS.tex, NULL, &gameUI.soundThreadFPS.rect);
    }

    void GraphicsHandler::renderUI()
    {
        renderThreadsInfo();
    }
}
