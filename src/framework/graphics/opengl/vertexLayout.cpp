
#include<oxu/framework/graphics/opengl/vertexLayout.hpp>
#include<oxu/framework/graphics/opengl/core.hpp>

namespace oxu::framework::graphics::opengl
{
    VertexLayoutElement::VertexLayoutElement(
        const unsigned int &type,
        const unsigned int &count
    ): type(type), count(count)
    {

    }

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