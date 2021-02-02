#pragma once

#include<SDL2/SDL.h>
#include<oXu/utils/vector2.hpp>
#include<oXu/graphics/texture.hpp>

namespace oxu::graphics
{
    class GenericBackend
    {
    public:
        ~GenericBackend() { destroy(); }
        virtual bool init(SDL_Window *game_window) { return false; };
        virtual void destroy() {  };
        virtual void clear() {  };
        virtual void render(SDL_Window *game_window) {  };
        virtual void copy_texture(
            const Vector2<float> &position,
            const Vector2<float> &size,
            const Texture &tex
        ) {  };
    };
}
