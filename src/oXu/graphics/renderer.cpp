#include"renderer.hpp"

#include<memory>
#include<oXu/core/logger.hpp>
#include<oXu/graphics/opengl/renderer.hpp>
#include<oXu/graphics/genericBackend.hpp>
#include<oXu/graphics/opengl/renderer.hpp>

namespace oxu::graphics::Renderer
{
    static SDL_Window *cp_window;
    static std::unique_ptr<graphics::GenericBackend> 
    cp_current_backend = nullptr;
    static std::uint8_t 
    c_current_backend_enum;

    std::uint8_t get_current_backend_enum()
    {
        return c_current_backend_enum;
    }

    bool init(SDL_Window *window, std::uint8_t backend)
    {
        cp_window = window;
        c_current_backend_enum = backend;

        switch(backend)
        {
        case Backends::OPENGL:
            cp_current_backend = 
                std::make_unique<opengl::Renderer>();
            break;

        default:
            OXU_LOG_ERR("Tried to init renderer with unknown enum {}", backend);
            return false;
        }

        return cp_current_backend->init(cp_window);
    }

    void destroy()
    {
        cp_current_backend->destroy();
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
        const Texture &tex
    )
    {
        cp_current_backend->copy_texture(position, size, tex);
    }
}