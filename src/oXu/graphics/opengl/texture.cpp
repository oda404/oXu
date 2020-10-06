#include"texture.hpp"

#include<oXu/graphics/opengl/core.hpp>

#include<oXu/graphics/utils/img.hpp>

namespace oxu::OpenGL
{
    Texture::Texture(const std::string &path)
    {
        image.load(path.c_str());
        oxu_glCall_Assert(glGenTextures(1, &m_id));

        bind(0);
            oxu_glCall_Assert(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            oxu_glCall_Assert(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            oxu_glCall_Assert(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            oxu_glCall_Assert(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

            oxu_glCall_Assert(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.getBuffer()[0]));
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
        oxu_glCall_Assert(glActiveTexture(GL_TEXTURE0 + slot));
        oxu_glCall_Assert(glBindTexture(GL_TEXTURE_2D, m_id));
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    const uint32_t &Texture::getWidth() const
    {
        return image.getWidth();
    }

    const uint32_t &Texture::getHeight() const
    {
        return image.getHeight();
    }

    VertexArrayObject &Texture::getVao()
    {
        return m_vao;
    }
}