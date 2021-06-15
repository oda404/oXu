// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/input/handler.hpp>
#include<SDL2/SDL_events.h>

namespace oxu::InputHandler
{
    static SDL_Event c_event;

    void handleInput(bool &w_isClosed)
    {
        while(SDL_PollEvent(&c_event))
        {
            switch(c_event.type)
            {
                case SDL_QUIT:
                    w_isClosed = true;
                    break;
            }
        }
    }

}
