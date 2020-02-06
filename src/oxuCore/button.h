#pragma once
#include<SFML/Graphics.hpp>

namespace oxu
{
    namespace Action
    {
        enum
        {
            ChangeScene  = 0,
            TriggerEvent = 1,

        };
    }

    class Button
    {
    private:
        sf::Vector2f buttonPos;
        sf::Vector2f buttonSize;
        std::uint8_t buttonAction;
    public:
        Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize, std::uint8_t buttonAction):
        buttonPos(buttonPos), buttonSize(buttonSize), buttonAction(buttonAction)
        {
            
        }

        void handleButton(std::uint8_t &sceneID)
        {
            if(sceneID != buttonAction)
            {
                if(buttonAction == 1)
                {
                    
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    sceneID = buttonAction;
                }
            }
        }

    };
}