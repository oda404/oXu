// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_events.h>

#include<vector>

#include"../utils/vector2.hpp"

namespace oxu
{
    struct Click
    {
        Vector2<int> mousePos;
        uint32_t     clickTimeStamp;

        Click(const Vector2<int> &pMousePos, const uint32_t &pClickTimeStamp);
    };

    class InputHandler
    {
    private:
        InputHandler();

        SDL_Event event;
        std::vector<Click> clicks;

    public:
        /* ================== Singleton stuff ================ */
        static InputHandler &getInstance();
        
        InputHandler(const InputHandler&)            = delete;

        InputHandler(InputHandler&&)                 = delete;

        InputHandler& operator=(const InputHandler&) = delete;

        InputHandler& operator=(InputHandler&&)      = delete;
        /* ==================================================== */

        void init();

        void handleInput(bool &w_isClosed);
    };
}
