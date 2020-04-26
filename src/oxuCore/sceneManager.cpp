#include "sceneManager.hpp"

oxu::SceneManager::SceneManager() { }

bool oxu::SceneManager::init(SDL_Window *window)
{
    return graphicsHandler.init(window);
}

void oxu::SceneManager::handleCurrentSceneGraphics()
{
    graphicsHandler.render();
}

void oxu::SceneManager::handleCurrentSceneInput()
{
    inputHandler.handleInput();
}