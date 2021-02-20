#pragma once

#include<SDL2/SDL.h>
#include<oXu/utils/vector2.hpp>
#include<oXu/graphics/texture.hpp>

namespace oxu::graphics
{
    class GenericBackend
    {
    public:
        virtual ~GenericBackend() = default;
        virtual bool init(SDL_Window *game_window) = 0;
        virtual void destroy() = 0;
        virtual void clear() = 0;
        virtual void render(SDL_Window *game_window) = 0;
        virtual void copy_texture(
            const Vector2<float> &position,
            const Vector2<float> &size,
            const Texture &tex,
            float alpha = 1.0f
        ) = 0;
    };
}
