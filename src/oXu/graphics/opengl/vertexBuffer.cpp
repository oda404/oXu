#include"vertexBuffer.hpp"

#include<oXu/graphics/opengl/core.hpp>

namespace oxu::graphics::opengl
{
    VertexBuffer::VertexBuffer(const void *data, unsigned int size)
    {
        glGenBuffers(1, &m_id);
        bind();
        GL_CALL_ASSERT(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
        unbind();
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::modifyData(const void *data, unsigned int size) const
    {
        bind();
        GL_CALL_ASSERT(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
        unbind();
    }
}