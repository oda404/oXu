// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

namespace oxu
{
    struct StatusCodes
    {
        static int statusCode;
        enum
        {
            OK,
            SDL_INIT_FAIL,
            IMG_INIT_FAIL,
            WINDOW_CREATE_FAIL,
            RENDERER_CREATE_FAIL,
            MIX_OPEN_FAIL,
            MIX_INIT_FAIL,
        };
    };
}