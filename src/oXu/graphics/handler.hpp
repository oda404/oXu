// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include<oXu/beatmap/songManager.hpp>
#include<oXu/skin/skinManager.hpp>

namespace oxu::GraphicsHandler
{
    void init(SDL_Window *window_p, SongManager *songManager_p, SkinManager *skinManager_p);
}
