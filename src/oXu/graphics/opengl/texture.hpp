#pragma once

#include<oXu/graphics/opengl/vertexArrayObject.hpp>
#include<oXu/graphics/utils/png.hpp>
#include<string>
#include<vector>

namespace oxu::graphics::opengl
{
    class Texture
    {
    private:
        VertexArrayObject m_vao;
        unsigned int m_id;
        Png image;

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