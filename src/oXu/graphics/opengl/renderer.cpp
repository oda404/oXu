#include"renderer.hpp"

#include<glad/glad.h>

#include<vector>

#include<oXu/graphics/opengl/core.hpp>
#include<oXu/graphics/opengl/shader.hpp>
#include<oXu/graphics/opengl/indexBuffer.hpp>
#include<oXu/graphics/opengl/vertexArrayObject.hpp>
#include<oXu/graphics/opengl/vertexLayout.hpp>
#include<oXu/graphics/opengl/texture.hpp>
#include<oXu/core/scaling.hpp>

#include<oXu/utils/logger.hpp>

#define SCREEN_START_COORD -1.0f
#define SCREEN_END_COORD 1.0f

namespace oxu::OpenGL::Renderer
{
    enum Shaders
    {
        TEXTURE = 0
    };

    std::vector<Shader> c_shaders;
    SDL_GLContext c_GL_context;

    static float getNormalizedScreenCoord(float coord, bool xAxis)
    {
        return SCREEN_START_COORD + (coord * (SCREEN_END_COORD -  SCREEN_START_COORD)) / (xAxis ? (float)Scaling::screenSize.x : (float)Scaling::screenSize.y);
    }

    bool init(SDL_Window *p_window_p)
    {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        c_GL_context = SDL_GL_CreateContext(p_window_p);

        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            OXU_LOG_ERR("Failed to initialize glad");
            return false;
        }

        OXU_LOG_DEBUG("OpenGL {}.{}", GLVersion.major, GLVersion.minor);

        oxu_glCall_Assert(glEnable(GL_BLEND));
        oxu_glCall_Assert(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        oxu_glCall_Assert(glClearColor(0.f, 0.f, 0.f, 1.0f));

        c_shaders.emplace_back("../src/oXu/graphics/opengl/shaders/tex.glsl");

        return true;
    }

    void destroy()
    {
        SDL_GL_DeleteContext(c_GL_context);
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void drawTexture(
        const Vector2<float> &position,
        const Vector2<float> &size,
        OpenGL::Texture &GL_tex
    )
    {
        float normX = getNormalizedScreenCoord(position.x, true);
        float normY = getNormalizedScreenCoord(position.y + size.y, false) * SCREEN_START_COORD;

        float normXW = getNormalizedScreenCoord(position.x + size.x, true);
        float normYH = getNormalizedScreenCoord(position.y, false) * SCREEN_START_COORD;

        float vbData[] = {
            normX, normY, 0.0f, 0.0f,
            normXW, normY, 1.0f, 0.0f,
            normXW, normYH, 1.0f, 1.0f,
            normX, normYH, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GL_tex.getVao().bind();
        GL_tex.getVao().modifyVertexBuffer<float>(vbData, 16);
        GL_tex.bind(0);
        
        c_shaders[Shaders::TEXTURE].bind();
        c_shaders[Shaders::TEXTURE].setUniform1i("u_textureSlot", 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
    }
}