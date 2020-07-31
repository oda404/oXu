// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"inputHandler.hpp"

int eventWatch(void *userdata, SDL_Event *event)
{
    

    return 1;
}

void oxu::InputHandler::init()
{
    /* Add an event watch to check if a key is pressed */
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
