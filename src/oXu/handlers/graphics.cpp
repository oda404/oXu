// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphics.hpp"

namespace oxu
{
    bool GraphicsHandler::init(SDL_Window *window, bool *windowState, SongManager *songManager)
    {
        this->songManager = songManager;
        this->windowState = windowState;
        this->window = window;

        /* maybe redundant since I don't use the openGL context directly
        but i'm gonna leave it here just in case */
        context = SDL_GL_GetCurrentContext();

        thisThread = &Threads::instance().threads[GRAPHICS_THREAD];
        thisThread->maxFPS = 240;
        thisThread->thread = std::make_shared<std::thread>([this] { initThread(); });

        while(!doneInit);

        return true;
    }

    GraphicsHandler::~GraphicsHandler()
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        SDL_GL_DeleteContext(context);
    }

    bool GraphicsHandler::initThread()
    {
        thisThread->timer.start();

        SDL_GL_MakeCurrent(window, context);
        SDL_SetHint("SDL_RENDER_BATCHING", "1");
        SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "1");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(!renderer)
        {
            LOG_ERR(SDL_GetError());
            StatusCodes::statusCode = StatusCodes::RENDERER_CREATE_FAIL;
            return false;
        }

        if(!text.init())
        {
            return false;
        }

        skinManager.enumerateSkins();
        currentSkin = &skinManager.getSkin(0);
        currentSkin->loadTextures(renderer);
        currentSkin->setCursor();

        currentBeatmap = &songManager->getSong(1).getBeatmap(0);

        doneInit = true;

        startThread();

        return true;
    }

    void GraphicsHandler::startThread()
    {
        while(!*windowState)
        {
            thisThread->calculateDelta();

            SDL_RenderClear(renderer);
                        
            std::unique_lock<std::mutex> lockGuard(Threads::instance().mtx);

                renderThreadsInfo();
                renderHitCircles();

            lockGuard.unlock();

            SDL_RenderPresent(renderer);

            thisThread->limitFPS();
        }
    }

    void GraphicsHandler::renderHitCircles()
    {
        for(int32_t i = currentBeatmap->objTopCap; i >= currentBeatmap->objBotCap; --i)
        {
            currentBeatmap->hitObjects[i].approachCircle(thisThread->delta, currentBeatmap->difficulty.approachRateMs);

            SDL_RenderCopy(renderer, currentSkin->getTexture(Tex::HIT_CIRCLE), NULL, currentBeatmap->hitObjects[i].getHCRect());
            SDL_RenderCopy(renderer, currentSkin->getTexture(Tex::APPROACH_CIRCLE), NULL, currentBeatmap->hitObjects[i].getACRect());
            SDL_RenderCopy(renderer, currentSkin->getTexture(Tex::HIT_CIRCLE_OVERLAY), NULL, currentBeatmap->hitObjects[i].getHCRect());
        }
    }

    void GraphicsHandler::renderThreadsInfo()
    {        
        graphicsThreadFPS.text = "Graphics thread: " + std::to_string(static_cast<int>(1.0 / thisThread->delta)) + " FPS";
        text.createTexture(renderer, graphicsThreadFPS);
        graphicsThreadFPS.rect.x = Scaling::screenSize.x - graphicsThreadFPS.rect.w - 10;
        graphicsThreadFPS.rect.y = 10;

        inputThreadFPS.text = "Input thread: " + std::to_string(static_cast<int>(1.0 / Threads::instance().threads[MAIN_THREAD].delta)) + " FPS";
        text.createTexture(renderer, inputThreadFPS);
        inputThreadFPS.rect.x = Scaling::screenSize.x - inputThreadFPS.rect.w - 10;
        inputThreadFPS.rect.y = graphicsThreadFPS.rect.y + graphicsThreadFPS.rect.h + 10;

        SDL_RenderCopy(renderer, graphicsThreadFPS.tex, NULL, &graphicsThreadFPS.rect);
        SDL_RenderCopy(renderer, inputThreadFPS.tex, NULL, &inputThreadFPS.rect);
    }
}
