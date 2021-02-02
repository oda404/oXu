#pragma once

#include<SDL2/SDL.h>

#include<cstdint>

#include<oXu/utils/vector2.hpp>
#include<oXu/graphics/texture.hpp>
#include<oXu/graphics/opengl/renderer.hpp>

namespace oxu::Renderer
{
    enum Backends
    {
        OPENGL
    };

    bool init(SDL_Window *window, std::uint8_t backend);
    void destroy();
    void clear();
    void render();
    void copy_texture(
        const Vector2<float> &position, 
        const Vector2<float> &size, 
        const Texture &tex
    );
}