#include"indexBuffer.hpp"

#include<oXu/graphics/opengl/core.hpp>

namespace oxu::graphics::opengl
{
    IndexBuffer::IndexBuffer(const unsigned int *indices, unsigned int count)
    {
        oxu_glCall_Assert(glGenBuffers(1, &m_id));
        bind();
        oxu_glCall_Assert(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
        unbind();
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void IndexBuffer::bind() const
    {
        oxu_glCall_Assert(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}