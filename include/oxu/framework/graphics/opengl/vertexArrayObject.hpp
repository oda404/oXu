#pragma once

#include<memory>
#include<vector>

#include<oxu/framework/graphics/opengl/vertexBuffer.hpp>
#include<oxu/framework/graphics/opengl/vertexLayout.hpp>

namespace oxu::framework::graphics::opengl
{
    class VertexArrayObject
    {
    private:
        unsigned int m_id = 0;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;

    public:
        VertexArrayObject();
        ~VertexArrayObject();

        template<typename T>
        void setVertexBuffer(const void *data, unsigned int count);

        template<typename T>
        void modifyVertexBuffer(const void *data, unsigned int count) const;

        void setVertexLayout(const VertexLayout &vertexLayout);

        void bind() const;
        void unbind() const;
    };
}