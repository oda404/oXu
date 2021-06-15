#pragma once

namespace oxu::graphics::opengl
{
    class VertexBuffer
    {
    private:
        unsigned int m_id = 0;
    
    public:
        VertexBuffer(const void *data, unsigned int size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
        void modifyData(const void *data, unsigned int size) const;
    };
}