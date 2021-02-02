#pragma once

namespace oxu::graphics::opengl
{
    struct VertexLayoutElement
    {
        unsigned int type;
        unsigned int count;
        
        VertexLayoutElement(const unsigned int &type, const unsigned int &count);
    };
}