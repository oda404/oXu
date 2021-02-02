#pragma once

#include<string>

#include<oXu/graphics/opengl/texture.hpp>

namespace oxu::graphics
{
    class Texture
    {
    private:
        opengl::Texture *m_GL_tex = nullptr;

    public:
        ~Texture();
        Texture(const std::string &path);
        Texture();
        bool load(const std::string &path);
        const opengl::Texture *getGLTexture() const;
    };
}