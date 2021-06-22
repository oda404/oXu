
#include<oxu/framework/window.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/logger.hpp>
#include<string>

#define OXU_PX_DIVIDER 480.f

namespace oxu::framework
{

static SDL_Window *g_sdl_window = nullptr;

bool window::init(
    const std::string  &name,
    const Vector2<std::uint16_t> &size
)
{
    std::uint32_t flags = 
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

    g_sdl_window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        size.x,
        size.y,
        flags
    );
    
    if(!g_sdl_window)
    {
        status::set(status::WINDOW_INIT_FAIL);
        OXU_LOG_DEBUG(SDL_GetError());
        return false;
    }

    return true;
}

void window::destroy()
{
    SDL_DestroyWindow(g_sdl_window);
}

SDL_Window *window::get_native_window()
{
    return g_sdl_window;
}

Vector2<int> window::get_window_size()
{
    Vector2<int> ret;
    if(g_sdl_window)
        SDL_GetWindowSize(g_sdl_window, &ret.x, &ret.y);
    return ret;
}

void window::set_window_size(const Vector2<std::uint16_t> &size)
{
    if(g_sdl_window)
        SDL_SetWindowSize(g_sdl_window, size.x, size.y);
}

}
