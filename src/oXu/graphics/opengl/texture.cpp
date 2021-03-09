#include"texture.hpp"

#include<oXu/graphics/opengl/core.hpp>

namespace oxu::graphics::opengl
{
    Texture::Texture(const std::string &path)
    {
        m_png.load(path.c_str());
        glGenTextures(1, &m_id);

        bind(0);
        GL_CALL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CALL_ASSERT(
            glTexImage2D(
                GL_TEXTURE_2D, 
                0, 
                GL_RGBA8, 
                m_png.getWidth(), 
                m_png.getHeight(), 
                0, 
                GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                m_png.getBuffer()
            )
        );
        unbind();

        m_vao.bind();

        m_vao.setVertexBuffer<float>(NULL, 16);

        VertexLayout vertexLayout;
        /* position */
        vertexLayout.pushElement<float>(2);
        /* tex coords */
        vertexLayout.pushElement<float>(2);
        m_vao.setVertexLayout(vertexLayout);

        m_vao.unbind();
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_id);
    }

    void Texture::bind(const unsigned int slot) const
    {
        GL_CALL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::uint32_t Texture::getWidth() const
    {
        return m_png.getWidth();
    }

    std::uint32_t Texture::getHeight() const
    {
        return m_png.getHeight();
    }

    const VertexArrayObject &Texture::getVao() const
    {
        return m_vao;
    }
}