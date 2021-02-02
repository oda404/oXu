#include"texture.hpp"

#include<oXu/graphics/renderer.hpp>

namespace oxu::graphics
{
    Texture::Texture(const std::string &path)
    {
        m_GL_tex = std::make_unique<opengl::Texture>(path);
    }

    Texture::Texture()
    {

    }

    void Texture::load(const std::string &path)
    {
        m_GL_tex = std::make_unique<opengl::Texture>(path);
    }
}