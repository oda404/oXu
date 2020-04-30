#pragma once

#include "../handlers/graphicsHandler.hpp"
#include "../handlers/inputHandler.hpp"

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