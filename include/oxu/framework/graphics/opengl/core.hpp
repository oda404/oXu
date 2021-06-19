#pragma once

#include<glad/glad.h>

#include<oxu/framework/logger.hpp>

#define GL_CALL_LOG(func)\
glClearErrors();\
func;\
{\
unsigned int err;\
if(glHasError(err)) {\
    OXU_LOG_ERROR_EXT("[OpenGL] Error: {}", err);\
}\
}

#define GL_CALL_ASSERT(func)\
glClearErrors();\
func;\
{\
unsigned int err;\
if(glHasError(err)) {\
    OXU_LOG_ERROR_EXT("[OpenGL] Error: {}", err);\
    abort();\
}\
}

namespace oxu::framework::graphics::opengl
{
    void glClearErrors();
    bool glHasError(unsigned int &err);
}
