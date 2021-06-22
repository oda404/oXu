#pragma once

#include<SDL2/SDL.h>

#include<cstdint>

#include<oxu/framework/utils/vector2.hpp>
#include<oxu/framework/graphics/texture.hpp>

namespace oxu::framework::graphics::renderer
{
    enum Backends
    {
        OPENGL
    };

    std::uint8_t get_current_backend_enum();
    bool init(
        SDL_Window *window, 
        std::uint8_t backend,
        std::string config_dir_path
    );
    void destroy();
    void clear();
    void render();
    void copy_texture(
        const framework::Vector2<float> &position, 
        const framework::Vector2<float> &size, 
        const Texture &tex,
        float alpha = 1.0f
    );
}