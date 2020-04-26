#pragma once

#include "../oxuGameHandlers/graphicsHandler.hpp"
#include "../oxuGameHandlers/inputHandler.hpp"

namespace oxu
{
    class SceneManager
    {
    private:
        GraphicsHandler graphicsHandler;
        InputHandler    inputHandler;

    public:
        SceneManager();

        bool init(SDL_Window *window);

        void handleCurrentSceneGraphics();

        void handleCurrentSceneInput();
    };
}