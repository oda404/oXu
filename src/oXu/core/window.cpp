#include"window.hpp"

#define OXU_PX_DIVIDER 480.f

namespace oxu::window
{
    static Vector2<uint16_t> window_size;
    static float oxu_px;

    float get_oxu_px()
    {
        return oxu_px;
    }

    Vector2<std::uint16_t> get_window_size()
    {
        return window_size;
    }

    void set_window_size(SDL_Window *p_target_window_p, Vector2<std::uint16_t> new_size_p)
    {
        SDL_SetWindowSize(p_target_window_p, new_size_p.x, new_size_p.y);
        window_size = new_size_p;
        oxu_px = window_size.y / OXU_PX_DIVIDER;
    }
}
