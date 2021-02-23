#pragma once

#include<SDL2/SDL.h>

#include<oXu/utils/vector2.hpp>
#include<oXu/graphics/texture.hpp>
#include<oXu/graphics/genericBackend.hpp>

namespace oxu::graphics::opengl
{
    class Backend : public graphics::GenericBackend
    {
    public:
        bool init(SDL_Window *p_window, std::string configDirPath) override;
        void destroy() override;
        void clear() override;
        void render(SDL_Window *game_window) override;
        void copy_texture(
            const Vector2<float> &position, 
            const Vector2<float> &size, 
            const graphics::Texture &GL_tex,
            float alpha = 1.0f
        ) override;
        
        virtual ~Backend();
    };
}