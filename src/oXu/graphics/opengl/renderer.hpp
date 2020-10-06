#pragma once

#include<SDL2/SDL.h>

#include<oXu/utils/vector2.hpp>
#include<oXu/graphics/opengl/texture.hpp>

namespace oxu::OpenGL::Renderer
{
    bool init(SDL_Window *p_window);
    void destroy();
    void clear();
    void drawTexture(
        const Vector2<float> &position, 
        const Vector2<float> &size, 
        OpenGL::Texture &GL_tex
    );
}