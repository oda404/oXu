#pragma once

#include<SDL2/SDL_mouse.h>

#include<string>

#include<oxu/framework/graphics/texture.hpp>
#include<oxu/skin/config.hpp>

namespace oxu
{
    class Skin
    {
    private:
        std::string path;
        std::string name;
        framework::graphics::Texture textures[MAX_TEX_COUNT];
        SDL_Cursor *customCursor = NULL;

    public:
        Skin(const std::string &path_p);

        const framework::graphics::Texture 
        &getTexture(uint8_t texEnum) const;
        
        void setCursor();
        /* Required the renderer to be initiated */
        void loadTextures();
    };
}