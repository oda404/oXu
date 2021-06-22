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
    std::string m_path;
    std::string m_name;
    framework::graphics::Texture m_textures[MAX_TEX_COUNT];
    SDL_Cursor *m_cursor = NULL;

public:
    Skin(const std::string &path);

    const framework::graphics::Texture 
    &getTexture(uint8_t texEnum) const;
    
    void setCursor();
    /* Required the renderer to be initiated */
    void loadTextures();

    std::string get_name() const;
};

}