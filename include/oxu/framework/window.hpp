
#pragma once

#include<SDL2/SDL.h>
#include<cstdint>
#include<oxu/framework/utils/vector2.hpp>

namespace oxu::framework::window
{

enum InitFlags
{
    FULLSCREEN = 0x1,
    OPENGL     = 0x2,
    SHOWN      = 0x4,
    HIDDEN     = 0x8
};

bool init(
    const std::string  &name,
    const Vector2<std::uint16_t> &size
);
void destroy();

SDL_Window *get_native_window();
void set_window_size(const Vector2<std::uint16_t> &size);
Vector2<int> get_window_size(); 

}
