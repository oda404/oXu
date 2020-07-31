// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"graphicsHandler.hpp"

namespace oxu
{
    bool GraphicsHandler::init(SDL_Window *window, std::shared_ptr<std::thread> *graphicsThread, double *inputThreadDelta, bool *windowState, SongManager *songManager)
    {
        this->window = window;

        this->songManager = songManager;

        this->windowState = windowState;

        this->inputThreadDelta = inputThreadDelta;

        /* get the current context */
        context = SDL_GL_GetCurrentContext();

        /* Create the thread */
        *graphicsThread = std::make_shared<std::thread>([this] { render(); });

        if(!text.init())
        {
            return false;
        }

        /* Wait for the new thread to finish initiating
        to avoid any context problems */
        while(!doneInit);

        return true;
    }

    GraphicsHandler::~GraphicsHandler()
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        SDL_GL_DeleteContext(context);
    }

    bool GraphicsHandler::render()
    {
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

        texturesI.createTextures(renderer);

        doneInit = true;

        while(!*windowState)
        {
            calculateDelta();

            SDL_RenderClear(renderer);
                        
            std::unique_lock<std::mutex> lockGuard(graphicsMutex);
            renderThreadInfo();
            renderHitCircles();
            lockGuard.unlock();

            SDL_RenderPresent(renderer);

            limitFPS();
        }

        return true;
    }

    void GraphicsHandler::renderHitCircles()
    {
        Beatmap &beatmap = songManager->getSong(1).getBeatmap(0);

        for(int32_t i = beatmap.objTopCap; i >= beatmap.objBotCap; --i)
        {
            beatmap.hitObjects[i].approachCircle(delta, beatmap.difficulty.approachRateMs);

            SDL_RenderCopy(renderer, texturesI.getHCTex(), NULL, beatmap.hitObjects[i].getHCRect());
            SDL_RenderCopy(renderer, texturesI.getACTex(), NULL, beatmap.hitObjects[i].getACRect());
            SDL_RenderCopy(renderer, texturesI.getHCOverlayTex(), NULL, beatmap.hitObjects[i].getHCRect());
        }
    }

    void GraphicsHandler::renderThreadInfo()
    {        
        graphicsThreadFPS.text = "Graphics thread: " + std::to_string(static_cast<int>(1.0 / delta)) + " FPS";
        text.createTexture(renderer, graphicsThreadFPS);
        graphicsThreadFPS.rect.x = Scaling::screenSize.x - graphicsThreadFPS.rect.w - 10;
        graphicsThreadFPS.rect.y = 10;

        inputThreadFPS.text = "Input thread: " + std::to_string(static_cast<int>(1.0 / *inputThreadDelta)) + " FPS";
        text.createTexture(renderer, inputThreadFPS);
        inputThreadFPS.rect.x = Scaling::screenSize.x - inputThreadFPS.rect.w - 10;
        inputThreadFPS.rect.y = graphicsThreadFPS.rect.y + graphicsThreadFPS.rect.h + 10;

        SDL_RenderCopy(renderer, graphicsThreadFPS.tex, NULL, &graphicsThreadFPS.rect);
        SDL_RenderCopy(renderer, inputThreadFPS.tex, NULL, &inputThreadFPS.rect);
    }

    void GraphicsHandler::calculateDelta()
    {
        lastTick  = startTick;
        startTick = SDL_GetTicks();
        delta = (startTick - lastTick) / 1000.0;
    }

    void GraphicsHandler::limitFPS()
    {
        if(1000.0 / maxFPS > SDL_GetTicks() - startTick)
        {
            SDL_Delay(1000.0 / maxFPS - SDL_GetTicks() + startTick);
        }
    }
}
