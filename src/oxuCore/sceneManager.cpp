#include"sceneManager.h"

oxu::SceneManager::SceneManager(sf::RenderWindow *window, PlayField *playFieldPtr):
playField(playFieldPtr) , currentScene(0)
{
    graphicsHandler.setCursor(window);

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
    graphicsHandler.drawCursor(window);
#endif
    
    //================  Actual scene handling  ==================
    soundHandler.handleSound(currentScene);
    graphicsHandler.handleGraphics(window, dt, currentScene);
    inputHandler.handleInput();
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
    hitObjects.createHitObjects(parser, *playField);
    graphicsHandler.loadInfo(&hitObjects, &soundHandler, playField);
}