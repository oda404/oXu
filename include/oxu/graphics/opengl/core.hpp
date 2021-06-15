#pragma once

#include<glad/glad.h>

#include<oxu/core/logger.hpp>

#define GL_CALL_LOG(func)\
glClearErrors();\
func;\
{\
unsigned int err;\
if(glHasError(err)) {\
    OXU_LOG_ERR_EXT("[OpenGL] Error: {}", err);\
}\
}

#define GL_CALL_ASSERT(func)\
glClearErrors();\
func;\
{\
unsigned int err;\
if(glHasError(err)) {\
    OXU_LOG_ERR_EXT("[OpenGL] Error: {}", err);\
    abort();\
}\
}

namespace oxu::graphics::opengl
{
    void glClearErrors();
    bool glHasError(unsigned int &err);
}
