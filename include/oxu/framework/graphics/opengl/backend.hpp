#pragma once

#include<SDL2/SDL.h>

#include<oxu/framework/utils/vector2.hpp>
#include<oxu/framework/graphics/texture.hpp>
#include<oxu/framework/graphics/genericBackend.hpp>

namespace oxu::framework::graphics::opengl
{
    class Backend : public graphics::GenericBackend
    {
    public:
        bool init(SDL_Window *p_window, std::string configDirPath) override;
        void destroy() override;
        void clear() override;
        void render(SDL_Window *game_window) override;
        void copy_texture(
            const framework::Vector2<float> &position, 
            const framework::Vector2<float> &size, 
            const graphics::Texture &GL_tex,
            float alpha = 1.0f
        ) override;
        
        virtual ~Backend();
    };
}