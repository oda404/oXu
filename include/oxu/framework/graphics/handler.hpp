// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>
#include<oxu/beatmap/songManager.hpp>
#include<oxu/skin/skinManager.hpp>

/*
Once initiated the graphics handler
spawns a new thread, initiates the renderer
and loads any given skin;
After that it sits in a loop and renders any
available hit objects. 
*/

namespace oxu::framework::graphics::handler
{

void init(
    SongManager *songManager_p, 
    SkinManager *skinManager_p,
    std::string config_dir_path_p
);
void shut_down();

}
