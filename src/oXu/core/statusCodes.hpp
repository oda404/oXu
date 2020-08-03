// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<cstdint>

namespace oxu::StatusCodes
{
    inline uint8_t code;
    enum
    {
        OK,
        SDL_INIT_FAIL,
        IMG_INIT_FAIL,
        WINDOW_CREATE_FAIL,
        RENDERER_CREATE_FAIL,
        MIX_OPEN_FAIL,
        MIX_INIT_FAIL,
        TTF_INIT_FAIL,
        FONT_LOAD_FAIL,
    };
}