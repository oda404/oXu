#pragma once

#include<vector>

namespace oxu::framework::graphics::opengl
{
    struct VertexLayoutElement
    {
    public:
        const unsigned int type;
        const unsigned int count;

        VertexLayoutElement(const unsigned int &type, const unsigned int &count);
    };

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