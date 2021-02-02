#include"vertexArrayObject.hpp"

#include<oXu/graphics/opengl/core.hpp>
#include<oXu/core/logger.hpp>

namespace oxu::graphics::opengl
{
    static unsigned int getGlTypeSize(unsigned int type)
    {
        switch(type)
        {
        case GL_FLOAT:
            return sizeof(float);
        case GL_INT:
            return sizeof(int);
        }

        return 0;
    }

    VertexArrayObject::VertexArrayObject()
    {
        oxu_glCall_Assert(glGenVertexArrays(1, &m_id));
    }

    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    template<>
    void VertexArrayObject::setVertexBuffer<float>(const void *data, unsigned int count)
    {
        m_vertexBuffer = std::make_unique<VertexBuffer>(data, count * sizeof(float));
    }

    template<>
    void VertexArrayObject::modifyVertexBuffer<float>(const void *data, unsigned int count) const
    {
        m_vertexBuffer->modifyData(data, count * sizeof(float));
    }

    void VertexArrayObject::setVertexLayout(const VertexLayout &vertexLayout)
    {
        m_vertexBuffer->bind();

        unsigned long int pointer = 0;

        for(unsigned int i = 0; i < vertexLayout.getElements().size(); ++i)
        {
            const VertexLayoutElement &element = vertexLayout.getElements()[i];
            
            oxu_glCall_Assert(glEnableVertexAttribArray(i));
            oxu_glCall_Assert(glVertexAttribPointer(i, element.count, element.type, false, vertexLayout.getStride(), (const void*)pointer));

            pointer += element.count * getGlTypeSize(element.type);
        }

        m_vertexBuffer->unbind();
    }

    void VertexArrayObject::bind() const
    {
        oxu_glCall_Assert(glBindVertexArray(m_id));
    }

    void VertexArrayObject::unbind() const
    {
        glBindVertexArray(0);
    }
}