// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once


#include"../components/gameComponents.hpp"

namespace oxu
{
    class InputHandler
    {
    private:
        GameComponents &gameComponentsI = GameComponents::getInstance();

    public:
        InputHandler();

        void handleInput();
    };
}
