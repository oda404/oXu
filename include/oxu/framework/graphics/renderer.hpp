#pragma once

#include<SDL2/SDL.h>

#include<cstdint>

#include<oxu/framework/utils/vector2.hpp>
#include<oxu/framework/graphics/texture.hpp>

namespace oxu::framework::graphics::renderer
{
    
enum class BackendType
{
    OPENGL
};

BackendType get_backend_type();
bool init(
    BackendType backend_type,
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