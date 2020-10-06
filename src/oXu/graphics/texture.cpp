#include"texture.hpp"

#include<oXu/graphics/renderer.hpp>

namespace oxu
{
    Texture::Texture(const std::string &path)
    {
        m_GL_tex = std::make_unique<OpenGL::Texture>(path);
    }

    Texture::Texture()
    {

    }

    void Texture::load(const std::string &path)
    {
        m_GL_tex = std::make_unique<OpenGL::Texture>(path);
    }
}