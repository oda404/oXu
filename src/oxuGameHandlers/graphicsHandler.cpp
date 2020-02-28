#include"graphicsHandler.hpp"

void oxu::GraphicsHandler::drawPendingObjectScoring(sf::RenderWindow &window, const float &dt)
{
    for(std::tuple<sf::Vector2f, uint8_t, uint8_t> &info: *inputHandler->getPendingObjScoring())
    {
        if(std::get<2>(info) - 400 * dt > 0)
        {
            sf::Sprite s(hitScoreTextures[std::get<1>(info)]);
            s.setOrigin(hitScoreTextures[std::get<1>(info)].getSize().x / 2, hitScoreTextures[std::get<1>(info)].getSize().y / 2);
            s.setPosition(std::get<0>(info));
            sf::Color c = s.getColor();
            std::get<2>(info) -= 400 * dt;
            s.setColor(sf::Color(c.r, c.g, c.b, std::get<2>(info)));

            window.draw(s);
        }
        else
            inputHandler->getPendingObjScoring()->erase(inputHandler->getPendingObjScoring()->begin());
    }
}

oxu::GraphicsHandler::GraphicsHandler(InputHandler *inputHandler, HitObjectManager *hitObjPtr, SoundHandler *soundHandlerPtr, PlayField *playFieldPtr, MapManager *mapManagerPtr, std::vector<MapSelectButton> *buttonsPtr):
inputHandler(inputHandler), hitObjects(hitObjPtr),  mapSound(soundHandlerPtr), playField(playFieldPtr), mapManager(mapManagerPtr), mapSelectButtons(buttonsPtr)
{
    sf::Texture t;
    t.loadFromFile("../skins/hit0.png");
    hitScoreTextures.push_back(t);
    t.loadFromFile("../skins/hit50.png");
    hitScoreTextures.push_back(t);
    t.loadFromFile("../skins/hit100.png");
    hitScoreTextures.push_back(t);

    //=====================  font and combo text  =================================
#ifdef __linux__
    font.loadFromFile("../textures/coolvetica.ttf");
#else
    font.loadFromFile("E:/visualproj/SFMLosuBootleg/textures/coolvetica.ttf"); 
#endif
    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(60);
    scoreText.setPosition(1800,50);
    comboString.setFont(font);
    comboString.setFillColor(sf::Color(255,255,255, 255));
    comboString.setCharacterSize(90);
    comboString.setPosition(35,940); 
    //===============================================================================
    xButton.setSize({960,20});
    zButton.setSize({-960,20});
    xButton.setPosition(960,1060);
    xButton.setFillColor(sf::Color::White);
    zButton.setPosition(960,1060);
    zButton.setFillColor(sf::Color::White);


    std::vector<std::function<void(sf::RenderWindow &window, const float &dt)>> aux;
    //add main menu graphics handlers @ index 0===========================================================================
    aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawMainMenu(window, dt); });

    sceneGraphicsHandlers.push_back(aux);

    aux.clear();
    //====================================================================================================================

    // add song select graphics handlers @ index 1========================================================================
    aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawSongSelectMenu(window, dt); });

    sceneGraphicsHandlers.push_back(aux);

    aux.clear();
    //====================================================================================================================

    //add game graphics handlers @ index 2==================================================================================
    aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawHitCircles(window, dt); });
    aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawGameOverlay(window, dt); });
    aux.push_back([this](sf::RenderWindow &window, const float &dt) -> void { return this->drawPendingObjectScoring(window, dt); });

    sceneGraphicsHandlers.push_back(aux);

    aux.clear();
    //======================================================================================================================
}

void oxu::GraphicsHandler::handleGraphics(sf::RenderWindow &window, const float &dt, const std::uint8_t &sceneID)
{
    for(auto handler: sceneGraphicsHandlers[sceneID])
    {
        handler(window,dt);
    }
    #ifdef __linux__
        drawCursor(&window, static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    #endif
}

void oxu::GraphicsHandler::drawHitCircles(sf::RenderWindow &window, const float &dt)
{
    if (mapSound->getAudioPlayingOffset() >= hitObjects->getHitCircleByIndex(hitObjects->getHitCircleIt() + 1)->getSpawnTime() - hitObjects->getApproachCircleByIndex(0)->getApproachSpeedAsMs())
        hitObjects->incrementHitCircleIt();

    for(int i = hitObjects->getHitCircleIt(); i >= hitObjects->getHitCircleCap(); --i)
    {
        if(!hitObjects->getApproachCircleByIndex(i)->getApproachState())
        {
            hitObjects->getHitCircleByIndex(i)->fadeCircleIn(dt);
            hitObjects->getApproachCircleByIndex(i)->fadeCircleIn(dt);           
                
            hitObjects->getApproachCircleByIndex(i)->approachTheCircle(dt, hitObjects->getHitCircleByIndex(i)->getHitCircleScale());

            window.draw(*hitObjects->getHitCircleByIndex(i)->getHitCircleOverlay());
            window.draw(*hitObjects->getApproachCircleByIndex(i)->getApproachCircle());
            window.draw(*hitObjects->getHitCircleByIndex(i)->getHitCircle());    
        }
        else
        {
            if(!hitObjects->getHitCircleByIndex(i)->fadeCircleOut(dt))
            {
                hitObjects->getApproachCircleByIndex(i)->fadeCircleOut(dt);
                
                window.draw(*hitObjects->getHitCircleByIndex(i)->getHitCircleOverlay());
                window.draw(*hitObjects->getApproachCircleByIndex(i)->getApproachCircle());
                window.draw(*hitObjects->getHitCircleByIndex(i)->getHitCircle());   
            }
            else
                hitObjects->incrementHitCircleCap();
        }
    }
}

void oxu::GraphicsHandler::drawGameOverlay(sf::RenderWindow &window, const float &dt)
{
    //======================  rectangles for each input key (x,z)  ===========================================
    sf::RectangleShape rec(sf::Vector2f({60,60}));
    rec.setPosition({1860,420});
    rec.setFillColor(sf::Color::White);
    rec.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 60));

    sf::RectangleShape rec1(sf::Vector2f({60,60}));
    rec1.setPosition({1860,540});
    rec1.setFillColor(sf::Color::White);
    rec1.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 60));

    if(inputHandler->getXKeyState())
        rec.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 125));

    if(inputHandler->getZKeyState())
        rec1.setFillColor(sf::Color(rec.getFillColor().r, rec.getFillColor().g, rec.getFillColor().b, 125));
    
    window.draw(rec1);
    window.draw(rec);
    //==========================================================================================================

    //======================================  combo  ===========================================================
    comboString.setString(std::to_string(inputHandler->getCombo()) + " x");
    window.draw(comboString);
    //==========================================================================================================

    //=====================================  score  ============================================================
    scoreText.setString(std::to_string(*inputHandler->getScore()));
    window.draw(scoreText);
    //==========================================================================================================
}

void oxu::GraphicsHandler::setCursor(sf::RenderWindow *window)
{
#ifdef __linux__
    window->setMouseCursorVisible(false);
    cursorTexture.loadFromFile("../skins/cursor.png");
    cursorSprite = std::make_shared<sf::Sprite>(cursorTexture);
    cursorSprite->setOrigin(static_cast<sf::Vector2f>(cursorTexture.getSize()) / 2.0f);
    cursorTrailTexture.loadFromFile("../skins/cursortrail.png");
#endif
}

#ifdef __linux__
void oxu::GraphicsHandler::drawCursor(sf::RenderWindow *window, sf::Vector2f mousePos)
{
    if(cursorTrailVector.size() < 20)
        cursorTrailVector.push_back(mousePos);
    else
        cursorTrailVector.erase(cursorTrailVector.begin());
    
    uint8_t alpha = 0;
    for(auto &pos: cursorTrailVector)
    {
        sf::Sprite trail(cursorTrailTexture);
        trail.setOrigin(static_cast<sf::Vector2f>(cursorTrailTexture.getSize()) / 2.0f);
        trail.setColor(sf::Color(trail.getColor().r, trail.getColor().g, trail.getColor().b, alpha));
        if(alpha + 10 < 255)
            alpha += 10;
        trail.setPosition(pos);

        window->draw(trail);
    }

    cursorSprite->setPosition(mousePos);
    window->draw(*cursorSprite);
}
#endif

void oxu::GraphicsHandler::drawMainMenu(sf::RenderWindow &window, const float &dt)
{
    static sf::Text text("Click anywhere to continue!",font);
    static uint8_t alpha = 255;
    static bool go = false;
    text.setPosition({0,0});
    text.setString("Click anywhere to continue!");
    text.setFillColor(sf::Color(255,255,255, alpha));

    int rate = 150;

    if(alpha - rate * dt < 0 && !go)
        go = true;
    else if (alpha - rate * dt > 0 && !go)
        alpha -= rate * dt;

    if(go && alpha + rate * dt > 255)
        go = false;
    else if (go && alpha + rate * dt < 255)
        alpha += rate * dt;

    text.setCharacterSize(35);
    text.setOrigin(text.getPosition().x + text.getLocalBounds().width / 2, text.getPosition().y + text.getLocalBounds().height / 2);
    text.setPosition(960,900);

    window.draw(text);

    text.setPosition(240,40);
    text.setFillColor(sf::Color(255,255,255, 122));
    text.setCharacterSize(30);
    text.setString("oXu has loaded " + std::to_string(mapManager->getNumberOfMaps()) + " beat maps!");

    window.draw(text);
}

void oxu::GraphicsHandler::drawSongSelectMenu(sf::RenderWindow &window, const float &dt)
{
    for(MapSelectButton &b: *mapSelectButtons)
    {
        b.drawButton(window);
    }
}