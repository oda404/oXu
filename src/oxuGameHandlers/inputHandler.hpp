#pragma once
#include<SFML/Graphics.hpp>

#include"hitObjectLoader.h"
#include"../oxuCore/button.h"

namespace oxu
{
    class InputHandler
    {
    public:
        InputHandler(const InputHandler&) = delete;

        static InputHandler& Get() { return s_InputHandler; }

        void handleInput(std::vector<Button> *buttons = nullptr, HitObjectLoader *hitObjects = nullptr)
        {
            
        }

    private:
        InputHandler() { }

        static InputHandler s_InputHandler;
    };
}