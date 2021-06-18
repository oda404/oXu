#pragma once

#include<string>

#include<oxu/framework/graphics/opengl/texture.hpp>

namespace oxu::framework::graphics
{
    namespace opengl
    {
        class Backend;
    }

    class Texture
    {
    private:
        friend class opengl::Backend;
        friend class GenericBackend;
        opengl::Texture *m_GL_tex = nullptr;

    public:
        ~Texture();
        Texture(const std::string &path);
        Texture();
        bool load(const std::string &path);
    };
}