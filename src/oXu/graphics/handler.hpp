// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>
#include<oXu/beatmap/songManager.hpp>
#include<oXu/skin/skinManager.hpp>

/*
Once initiated the graphics handler
spawns a new thread, initiates the renderer
and loads any given skin;
After that it sits in a loop and renders any
available hit objects. 
*/

namespace oxu::graphics::handler
{
    void init(SDL_Window *window_p, SongManager *songManager_p, SkinManager *skinManager_p);
    void shut_down();
}
