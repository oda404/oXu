// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"inputHandler.hpp"

int eventWatch(void *userdata, SDL_Event *event)
{
    /* Gets the exact mouse position + key timestamp when the key is pressed */
    if(event->type == SDL_KEYDOWN)
    {
        oxu::Vector2<int> mousePos;
        SDL_GetMouseState(&mousePos[0], &mousePos[1]);

        /* Cast the void* to Click* struct */
        std::vector<oxu::Click> *clicksVec = static_cast<std::vector<oxu::Click>*>(userdata);

        clicksVec->emplace_back(mousePos, event->key.timestamp);

        return 0;
    }

    return 1;
}

oxu::InputHandler::InputHandler() { }

void oxu::InputHandler::init()
{
    /* Add an event watch to check if a key is pressed */
    SDL_AddEventWatch(eventWatch, &clicks);
}

oxu::InputHandler &oxu::InputHandler::getInstance()
{
    static InputHandler instance;
    return instance;
}

void oxu::InputHandler::handleInput(bool &w_isClosed)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                w_isClosed = true;
                break;
        }
    }
}

oxu::Click::Click(const Vector2<int> &pMousePos, const uint32_t &pClickTimeStamp):
mousePos(pMousePos), clickTimeStamp(pClickTimeStamp)
{

}
