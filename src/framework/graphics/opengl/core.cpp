
#include<oxu/framework/graphics/opengl/core.hpp>
namespace oxu::framework::graphics::opengl
{
    void glClearErrors()
    {
        while(glGetError() != GL_NO_ERROR);
    }

    bool glHasError(unsigned int &err)
    {
        if((err = glGetError()) != GL_NO_ERROR)
        {
            return true;
        }

        return false;
    }
}