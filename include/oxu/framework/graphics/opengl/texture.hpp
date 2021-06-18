#pragma once

#include<oxu/framework/graphics/opengl/vertexArrayObject.hpp>
#include<oxu/framework/graphics/png.hpp>
#include<string>

namespace oxu::framework::graphics::opengl
{
    class Texture
    {
    private:
        VertexArrayObject m_vao;
        unsigned int m_id;
        Png m_png;

    public:
        Texture(const std::string &path);
        ~Texture();

        void bind(const unsigned int slot) const;
        void unbind() const;
        std::uint32_t getWidth() const;
        std::uint32_t getHeight() const;
        const VertexArrayObject &getVao() const;
    };
}