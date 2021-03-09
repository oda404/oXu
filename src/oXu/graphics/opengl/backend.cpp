#include"backend.hpp"

#include<glad/glad.h>
#include<vector>
#include<filesystem>

#include<oXu/graphics/opengl/core.hpp>
#include<oXu/graphics/opengl/shader.hpp>
#include<oXu/graphics/opengl/indexBuffer.hpp>
#include<oXu/graphics/opengl/vertexArrayObject.hpp>
#include<oXu/graphics/opengl/vertexLayout.hpp>
#include<oXu/graphics/opengl/texture.hpp>
#include<oXu/core/window.hpp>
#include<oXu/core/logger.hpp>

namespace oxu::graphics::opengl
{
    enum Shaders
    {
        TEXTURE = 0
    };

    static std::vector<Shader> c_shaders;
    static SDL_GLContext c_GL_context;

    inline static Vector2<float>
    get_normalized_x_coords(Vector2<float> coords)
    {
        return -1.0f + coords * 2.0f / window::get_window_size().x;
    }

    inline static Vector2<float>
    get_normalized_y_coords(const Vector2<float> &coords)
    {
        return (-1.0f + coords * 2.0f / window::get_window_size().y) * -1.0f;
    }

    Backend::~Backend()
    {
        destroy();
    }

    bool Backend::init(SDL_Window *p_window_p, std::string configDirPath)
    {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        c_GL_context = SDL_GL_CreateContext(p_window_p);

        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            OXU_LOG_ERR("Failed to initialize glad");
            return false;
        }

        OXU_LOG_DEBUG("[OpenGL] Version: {}.{}", GLVersion.major, GLVersion.minor);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.f, 0.f, 0.f, 1.0f);

        namespace stdfs = std::filesystem;

        c_shaders.emplace_back(stdfs::path(configDirPath) / "res/shaders/tex.glsl");

        return true;
    }

    void Backend::destroy()
    {
        c_shaders.clear();
        SDL_GL_DeleteContext(c_GL_context);
    }

    void Backend::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Backend::render(SDL_Window *game_window)
    {
        SDL_GL_SwapWindow(game_window);
    }

    void Backend::copy_texture(
        const Vector2<float> &position,
        const Vector2<float> &size,
        const graphics::Texture &tex,
        float alpha
    )
    {
        const Vector2<float> x_coords = 
        get_normalized_x_coords({ position.x, position.x + size.x });

        const Vector2<float> y_coords = 
        get_normalized_y_coords({ position.y, position.y + size.y });

        float vbData[] = {
            x_coords.x, y_coords.x, 0.0f, 0.0f,
            x_coords.y, y_coords.x, 1.0f, 0.0f,
            x_coords.y, y_coords.y, 1.0f, 1.0f,
            x_coords.x, y_coords.y, 0.0f, 1.0f
        };

        static unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        const opengl::VertexArrayObject &vao = 
        tex.m_GL_tex->getVao();

        vao.bind();
        vao.modifyVertexBuffer<float>(vbData, 16);

        tex.m_GL_tex->bind(0);
        
        c_shaders[Shaders::TEXTURE].bind();
        c_shaders[Shaders::TEXTURE].setUniform1i("u_textureSlot", 0);
        c_shaders[Shaders::TEXTURE].setUniform1f("u_alpha", alpha);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

        c_shaders[Shaders::TEXTURE].unbind();
        vao.unbind();
        tex.m_GL_tex->unbind();
    }
}