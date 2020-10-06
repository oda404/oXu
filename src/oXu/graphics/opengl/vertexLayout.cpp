#include"vertexLayout.hpp"

#include<oXu/graphics/opengl/core.hpp>

namespace oxu::OpenGL
{
    template<>
    void VertexLayout::pushElement<float>(unsigned int count)
    {
        m_elements.emplace_back(GL_FLOAT, count);
        m_stride += count * sizeof(float);
    }

    template<>
    void VertexLayout::pushElement<int>(unsigned int count)
    {
        m_elements.emplace_back(GL_INT, count);
        m_stride += count * sizeof(int);
    }

    const std::vector<VertexLayoutElement> &VertexLayout::getElements() const
    {
        return m_elements;
    }

    const unsigned int &VertexLayout::getStride() const
    {
        return m_stride;
    }
}