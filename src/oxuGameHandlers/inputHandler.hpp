#pragma once
#include<SFML/Graphics.hpp>
#include<future>

#include"hitObjectLoader.h"
#include"../oxuCore/button.h"

namespace oxu
{
    class InputHandler
    {
    private:

    public:
        InputHandler()
        {

        }
 
        static void init(sf::RenderWindow *window/*std::vector<Button> *buttons, HitObjectLoader *hitObjects*/)
        {
            while(window->isOpen())
            {
                
            }
        }
    };
}