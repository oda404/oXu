// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphics.hpp"

namespace oxu
{
    void GraphicsHandler::init(SDL_Window *window, bool *windowState, SongManager *songManager)
    {
        thisThread = &Threading::threads[GRAPHICS];
        thisThread->maxFPS = 240;

        this->songManager = songManager;
        this->windowState = windowState;
        this->window = window;

        /* maybe redundant since I don't use the openGL context directly
        but i'm gonna leave it here just in case */
        context = SDL_GL_GetCurrentContext();

        thisThread->thread = std::thread([this] { initThread(); });

        while(!doneInit);
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

        passwd *pwd;

        pwd = getpwuid(getuid());

        std::string dir;
        dir = "/home/";
        dir.append(pwd->pw_name);
        dir.append("/.config/oXu/res/fonts/Hack-Regular.ttf");

        font = TTF_OpenFont(dir.c_str(), 20);
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

        beatmap = &songManager->getSong(1).getBeatmap(0);

        doneInit = true;

        startThread();

        return true;
    }

    void GraphicsHandler::startThread()
    {
        thisThread->timer.start();

        while(!*windowState)
        {
            thisThread->calculateDelta();
            
            SDL_RenderClear(renderer);
                        
            std::unique_lock<std::mutex> lockGuard(Threading::mtx);

                renderThreadsInfo();
                renderHitCircles();

            lockGuard.unlock();

            SDL_RenderPresent(renderer);

            thisThread->limitFPS();
        }
    }

    void GraphicsHandler::renderHitCircles()
    {
        HitObject *obj;

        for(size_t i = beatmap->hitObjectsPool.size() - 1; i != SIZE_MAX; --i)
        {
            obj = beatmap->hitObjectsPool[i];

            SDL_RenderCopy(renderer, skin->getTexture(Tex::HIT_CIRCLE), NULL, obj->getHCRect());
            SDL_RenderCopy(renderer, skin->getTexture(Tex::APPROACH_CIRCLE), NULL, obj->getACRect());
            SDL_RenderCopy(renderer, skin->getTexture(Tex::HIT_CIRCLE_OVERLAY), NULL, obj->getHCRect());
        }
    }

    void GraphicsHandler::renderThreadsInfo()
    {
        static double renderTimer = 0.0;

        renderTimer += thisThread->delta;

        if(renderTimer >= 0.5)
        {
            renderTimer = 0.0;

            graphicsThreadFPS.text = "Graphics: " + std::to_string(Threading::threads[GRAPHICS].FPS) + " FPS";
            graphicsThreadFPS.createTexture(renderer, font);
            graphicsThreadFPS.rect.x = Scaling::screenSize.x - graphicsThreadFPS.rect.w - 10;
            graphicsThreadFPS.rect.y = 10;

            inputThreadFPS.text = "Input: " + std::to_string(Threading::threads[MAIN].FPS) + " FPS";
            inputThreadFPS.createTexture(renderer, font);
            inputThreadFPS.rect.x = Scaling::screenSize.x - inputThreadFPS.rect.w - 10;
            inputThreadFPS.rect.y = graphicsThreadFPS.rect.y + graphicsThreadFPS.rect.h + 10;
        }

        SDL_RenderCopy(renderer, graphicsThreadFPS.tex, NULL, &graphicsThreadFPS.rect);
        SDL_RenderCopy(renderer, inputThreadFPS.tex, NULL, &inputThreadFPS.rect);
    }
}
