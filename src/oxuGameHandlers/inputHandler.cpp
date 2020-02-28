#include"inputHandler.hpp"

oxu::InputHandler::InputHandler(HitObjectManager *hitObjManagerPtr, SoundHandler *soundHandlerPtr, MapManager *mapManagerPtr, std::vector<MapSelectButton> *mapSelectButtons):
hitObjManager(hitObjManagerPtr), soundHandler(soundHandlerPtr), mapManager(mapManagerPtr), mapSelectButtons(mapSelectButtons)
{
    //==========  main menu input handlers ====================
    sceneInputHandlers.push_back([this](sf::RenderWindow &window, std::uint8_t &currentScene) -> void { return this->handleMainMenuInput(window, currentScene); });

    //========== song select input handler ====================
    sceneInputHandlers.push_back([this](sf::RenderWindow &window, std::uint8_t &currentScene) -> void { return this->handleSongSelectInput(window, currentScene); });

    //========== game input handler ==========================
    sceneInputHandlers.push_back([this](sf::RenderWindow &window, std::uint8_t &currentScene) -> void { return this->handleHitObjectsInput(window, currentScene); });
}

float oxu::InputHandler::getApproachCirclePercentage(const float &spawnTime, const float &approachSpeed, const float &playingOffset) const
{
    return 100 - (spawnTime - playingOffset) * 100 / approachSpeed;
}

void oxu::InputHandler::hitObjectScoring(const int /* switch to float */ &ACPerc, const sf::Vector2f &objPos)
{
    if(ACPerc > 0 && ACPerc <= 103){
        switch(ACPerc)
        {
        case 0 ... 74: //miss
            // nothing
            pendingObjScoring.push_back(std::make_tuple(objPos, 0, 255));
            ++pendingObj;
            combo = 0;
            break;
        case 75 ... 84: //50
            score += 50;
            pendingObjScoring.push_back(std::make_tuple(objPos, 1, 255));
            ++pendingObj;
            ++combo;
            break;
        case 85 ... 94: //100
            score += 100;
            pendingObjScoring.push_back(std::make_tuple(objPos, 2, 255));
            ++pendingObj;
            ++combo;
            break;
        case 95 ... 103: //300
            score += 300;
            ++pendingObj;
            ++combo;
            break;
        }
        hitObjManager->incrementHitCircleCap();
    }
    else if(ACPerc > 103 && ACPerc <= 111){
        switch(ACPerc)
        {
        case 104 ... 107: //100
            score += 100;
            pendingObjScoring.push_back(std::make_tuple(objPos, 2, 255));
            ++pendingObj;
            ++combo;
            break;
        case 108 ... 111: //50
            score += 50;
            pendingObjScoring.push_back(std::make_tuple(objPos, 1, 255));
            ++pendingObj;
            ++combo;
            break;
        }
        hitObjManager->incrementHitCircleCap();
    }
}

void oxu::InputHandler::handleMainMenuInput(sf::RenderWindow &window, std::uint8_t &currentScene)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePressed)
    {
        mousePressed = true;
        ++currentScene;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mousePressed = false;
}

void oxu::InputHandler::handleSongSelectInput(sf::RenderWindow &window, std::uint8_t &currentScene)
{
    for(auto &button: *mapSelectButtons)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && button.checkClick(sf::Mouse::getPosition(window)) && !mousePressed)
        {
            mapManager->loadHitObjects(button.getMapPath());
            hitObjManager->createHitObjects(*mapManager, mapManager->getMapDifficulty(button.getMapPath()));
            mapManager->clearMapInfo();
            soundHandler->loadAudioFile(button.getSongPath().c_str());
            soundHandler->playAudio();

            mousePressed = true;
            ++currentScene;
        }
        else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            mousePressed = false;
    }
}

void oxu::InputHandler::handleHitObjectsInput(sf::RenderWindow &window, std::uint8_t &currentScene)
{
    if(kb.isKeyPressed(sf::Keyboard::X))
    {
        if(!xState){
            xState = true;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f circlePos = hitObjManager->getHitCircleByIndex(pendingObj)->getPos();
            float circleHalfScale = hitObjManager->getHitCircleSize() / 2;
            if(mousePos.x <= circlePos.x + circleHalfScale && mousePos.x >= circlePos.x - circleHalfScale &&
                mousePos.y <= circlePos.y + circleHalfScale && mousePos.y >= circlePos.y - circleHalfScale)
            {
                int ACPerc = getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), hitObjManager->getApproachCircleByIndex(0)->getApproachSpeedAsMs(), soundHandler->getAudioPlayingOffset());
                hitObjectScoring(ACPerc, circlePos);
            }
        }
    }
    else if(!kb.isKeyPressed(sf::Keyboard::X))
        xState = false;

    if(kb.isKeyPressed(sf::Keyboard::Z))
    {
        if(!zState){
            zState = true;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f circlePos = hitObjManager->getHitCircleByIndex(pendingObj)->getPos();
            float circleHalfScale = hitObjManager->getHitCircleSize() / 2;
            if(mousePos.x <= circlePos.x + circleHalfScale && mousePos.x >= circlePos.x - circleHalfScale &&
                mousePos.y <= circlePos.y + circleHalfScale && mousePos.y >= circlePos.y - circleHalfScale)
            {
                int ACPerc = getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), hitObjManager->getApproachCircleByIndex(0)->getApproachSpeedAsMs(), soundHandler->getAudioPlayingOffset());
                hitObjectScoring(ACPerc, circlePos);
            }
        }
    }
    else if(!kb.isKeyPressed(sf::Keyboard::Z))
        zState = false;

    if(getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), hitObjManager->getApproachCircleByIndex(0)->getApproachSpeedAsMs(), soundHandler->getAudioPlayingOffset()) > 111)
    {
        pendingObjScoring.push_back(std::make_tuple(hitObjManager->getHitCircleByIndex(pendingObj)->getPos(), 0, 255));
        combo = 0;
        ++pendingObj;
    }
}

bool oxu::InputHandler::getXKeyState() const { return xState; }

bool oxu::InputHandler::getZKeyState() const { return zState; }

int oxu::InputHandler::getCombo() const { return combo; }

uint32_t *oxu::InputHandler::getScore() { return &score; }

std::vector<std::tuple<sf::Vector2f, uint8_t, uint8_t>> *oxu::InputHandler::getPendingObjScoring() { return &pendingObjScoring; }

void oxu::InputHandler::handleInput(sf::RenderWindow &window, std::uint8_t &sceneID)
{
    sceneInputHandlers[sceneID](window, sceneID);
}