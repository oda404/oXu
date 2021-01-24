#include"renderer.hpp"

#include<oXu/graphics/opengl/renderer.hpp>
#include<oXu/core/logger.hpp>

namespace oxu
{
    SDL_Window *cp_window;

    void Renderer::destroy()
    {
        OpenGL::Renderer::destroy();
    }

    void Renderer::init(SDL_Window *window)
    {
        cp_window = window;
        OpenGL::Renderer::init(cp_window);
    }

    void Renderer::drawTexture(const Vector2<float> &position, const Vector2<float> &size, const Texture &tex)
    {
        OpenGL::Renderer::drawTexture(position, size, *tex.m_GL_tex.get());
    }

    void Renderer::clear()
    {
        OpenGL::Renderer::clear();
    }

    void Renderer::render()
    {
        SDL_GL_SwapWindow(cp_window);
    }
}