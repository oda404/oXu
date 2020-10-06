#pragma once

#include<assert.h>

#include<glad/glad.h>

#include<oXu/utils/logger.hpp>

#define oxu_glCall_Log(x) glClearErrors();\
    x;\
    { unsigned int glErr;\
    if( glHasError(glErr) ) OXU_LOG_ERR_EXT("OpenGL error [{}]!", glErr); } 

#define oxu_glCall_Assert(x) glClearErrors();\
    x;\
    { unsigned int glErr;\
    if( glHasError(glErr) ) { OXU_LOG_ERR_EXT("OpenGL error [{}]!", glErr); abort(); } } 

namespace oxu::OpenGL
{
    void glClearErrors();
    bool glHasError(unsigned int &err);
}