
#include<filesystem>
#include<oxu/skin/skin.hpp>
#include<oxu/framework/logger.hpp>
#include<oxu/skin/config.hpp>
#include<oxu/framework/graphics/png.hpp>

namespace oxu
{

using namespace framework;

Skin::Skin(const std::string &path)
    : m_path(path), 
      m_name(path.substr(path.find_last_of('/') + 1, path.size() - 1))
{
    OXU_LOG_DEBUG("Found skin {}", m_name);
}

std::string Skin::get_name() const
{
    return m_name;
}

void Skin::loadTextures()
{
    namespace fs = std::filesystem;

    // free textures

    for(const fs::directory_entry &entry: fs::directory_iterator(m_path))
    {
        if(entry.path().extension() == ".png")
        {
            std::string textureName = entry.path().string().substr(entry.path().string().find_last_of('/') + 1, entry.path().string().size() - 1);

            std::map<std::string, std::uint8_t>::const_iterator pair = texNamesMap.find(textureName);

            if(pair->first != "")
            {
                m_textures[pair->second].load(entry.path().string());
            }
        }
    }
}

void Skin::setCursor()
{
    graphics::Png image(m_path + "/cursor.png");

    SDL_Surface *cursorSurface = 
    SDL_CreateRGBSurfaceFrom(
        (void*)image.getBuffer(), 
        image.getWidth(), 
        image.getHeight(), 
        image.getBPP(), 
        4 * image.getWidth(), 
        0x000000ff, 
        0x0000ff00, 
        0x00ff0000, 
        0xff000000
    );

    if(!cursorSurface)
    {
        OXU_LOG_WARN(SDL_GetError());
        return;
    }

    if(m_cursor)
    {
        SDL_FreeCursor(m_cursor);
        m_cursor = NULL;
    }

    m_cursor = SDL_CreateColorCursor(cursorSurface, cursorSurface->w / 2, cursorSurface->h / 2);

    SDL_FreeSurface(cursorSurface);

    SDL_SetCursor(m_cursor);
}

const graphics::Texture &Skin::getTexture(uint8_t texNum) const
{
    if(texNum >= MAX_TEX_COUNT)
    {
        OXU_LOG_WARN("Tried to access a non existent texture, returned last texture in array!");
        return m_textures[MAX_TEX_COUNT - 1];
    }

    return m_textures[texNum];
}

}
