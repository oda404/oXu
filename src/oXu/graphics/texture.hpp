#pragma once

#include<string>
#include<memory>

#include<oXu/graphics/opengl/texture.hpp>

namespace oxu::graphics
{
    class Texture
    {
    public:
        std::unique_ptr<opengl::Texture> m_GL_tex;

    public:
        Texture(const std::string &path);
        Texture();
        void load(const std::string &path);
    };
}