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
        std::uint8_t buttonAction;
        std::uint8_t buttonScene;
    public:
        Button(const sf::Vector2f &pos, std::uint8_t action, std::uint8_t scene = 0):
        buttonPos(pos), buttonAction(action), buttonScene(scene)
        {

        }

        void pressButton()
        {
            if(buttonAction == 0 && buttonScene!= 0)
            {
                if(buttonScene == 2)
                {

                }
            }
        }

    };
}