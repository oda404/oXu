#pragma once

#include<cstdint>
#include<oXu/utils/vector2.hpp>
#include<SDL2/SDL.h>

namespace oxu::window
{
    struct Window
    {

    };
    
    Vector2<std::uint16_t> get_window_size();
    float get_oxu_px();
    /* Resizes the target_window and also recalculates oxu_px. */
    void set_window_size(SDL_Window *target_window, Vector2<std::uint16_t> new_size);
}
