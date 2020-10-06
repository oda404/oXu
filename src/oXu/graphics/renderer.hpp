#pragma once

#include<SDL2/SDL.h>

#include<cstdint>

#include<oXu/utils/vector2.hpp>
#include<oXu/graphics/texture.hpp>
#include<oXu/graphics/opengl/renderer.hpp>

namespace oxu
{
    class Renderer
    {
    public:
        ~Renderer();
        static void init(SDL_Window *window);
        static void clear();
        static void render();
        static void drawTexture(
            const Vector2<float> &position, 
            const Vector2<float> &size, 
            const Texture &tex
        );
    };
}