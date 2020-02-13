#pragma once
#include<SFML/Graphics.hpp>

#include"hitObjectLoader.h"

namespace oxu
{
    class InputHandler
    {
    private:
        
    public:

        InputHandler() { }
 
        void handleInput()
        {  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {

            }
        }
    };
}