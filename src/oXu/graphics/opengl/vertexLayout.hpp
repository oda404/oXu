#pragma once

#include<vector>

#include<oXu/graphics/opengl/vertexLayoutElement.hpp>

namespace oxu::graphics::opengl
{
    class VertexLayout
    {
    private:
        std::vector<VertexLayoutElement> m_elements;
        unsigned int m_stride = 0;

    public:
        template<typename T>
        void pushElement(unsigned int count);

        const std::vector<VertexLayoutElement> &getElements() const;
        const unsigned int &getStride() const;
    };
}