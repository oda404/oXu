#include"renderer.hpp"

#include<memory>
#include<oXu/core/logger.hpp>
#include<oXu/graphics/opengl/backend.hpp>
#include<oXu/graphics/genericBackend.hpp>

namespace oxu::graphics::Renderer
{
    static SDL_Window *cp_window;
    static GenericBackend
    *cp_current_backend = nullptr;
    static std::uint8_t 
    c_current_backend_enum;

    std::uint8_t get_current_backend_enum()
    {
        return c_current_backend_enum;
    }

    bool init(
        SDL_Window *window, 
        std::uint8_t backend,
        std::string config_dir_path
    )
    {
        cp_window = window;
        c_current_backend_enum = backend;

        switch(backend)
        {
        case Backends::OPENGL:
            destroy();
            cp_current_backend = new opengl::Backend();
            break;

        default:
            OXU_LOG_ERR("Tried to init renderer with unknown enum {}", backend);
            return false;
        }

        return cp_current_backend->init(cp_window, config_dir_path);
    }

    void destroy()
    {
        if(cp_current_backend)
        {
            delete cp_current_backend;
            cp_current_backend = nullptr;
        }
    }

    void clear()
    {
        cp_current_backend->clear();
    }

    void render()
    {
        cp_current_backend->render(cp_window);
    }

    void copy_texture(
        const Vector2<float> &position, 
        const Vector2<float> &size, 
        const Texture &tex,
        float alpha
    )
    {
        cp_current_backend->copy_texture(position, size, tex, alpha);
    }
}