#include"sceneManager.h"

oxu::SceneManager::SceneManager(sf::RenderWindow *window)
{
    playField =  std::make_shared<PlayField>(window->getSize());

    inputHandler = std::make_shared<InputHandler>(&hitObjects, &soundHandler);

    graphicsHandler = std::make_shared<GraphicsHandler>(inputHandler.get());
    
    graphicsHandler->setCursor(window);

    //============  create buttons for every scene  ==================
    std::vector<Button> aux;
    aux.emplace_back(sf::Vector2f({0,0}),sf::Vector2f({1920,1080}), 1);

    buttons.push_back(aux);
    aux.clear();
    //================================================================
}

void oxu::SceneManager::handleCurrentScene(sf::RenderWindow &window, const float &dt)
{
    static bool go = true;

    if(currentScene == 1)
        window.clear();
    else
            window.clear(sf::Color(100,100,100,255));
            
#ifdef __linux__
    graphicsHandler->drawCursor(window);
#endif
    
    //================  Actual scene handling  ==================
    /*inputHandler gets called between every other handler so
    it gets the most accurate results*/

    soundHandler.handleSound(currentScene);

    inputHandler->handleInput(window, currentScene);

    graphicsHandler->handleGraphics(window, dt, currentScene);

    inputHandler->handleInput(window, currentScene);
    //===========================================================

    for(auto button: buttons[0])
    {
        button.handleButton(currentScene);
        if(currentScene == 1 && go)
        {
            loadBeatMap();
            go = false;
        }
    }

    window.display();
}

void oxu::SceneManager::loadBeatMap()
{
    BeatMapParser parser;
    hitObjects.createHitObjects(parser, *playField.get());
    graphicsHandler->loadInfo(&hitObjects, &soundHandler, playField.get());
}