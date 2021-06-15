
#include<filesystem>
#include<oxu/skin/skin.hpp>
#include<oxu/core/logger.hpp>
#include<oxu/skin/config.hpp>
#include<oxu/graphics/utils/png.hpp>

namespace oxu
{
    Skin::Skin(const std::string &path_p):
    path(path_p), name(path_p.substr(path_p.find_last_of('/') + 1, path_p.size() - 1))
    {
        OXU_LOG_DEBUG("Found skin {}", name);
    }
    
    void Skin::loadTextures()
    {
        namespace fs = std::filesystem;

        // free textures

        for(const fs::directory_entry &entry: fs::directory_iterator(path))
        {
            if(entry.path().extension() == ".png")
            {
                std::string textureName = entry.path().string().substr(entry.path().string().find_last_of('/') + 1, entry.path().string().size() - 1);

                std::map<std::string, std::uint8_t>::const_iterator pair = texNamesMap.find(textureName);

                if(pair->first != "")
                {
                    textures[pair->second].load(entry.path().string());
                }
            }
        }
    }

    void Skin::setCursor()
    {
        graphics::Png image(path + "/cursor.png");

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

        if(customCursor)
        {
            SDL_FreeCursor(customCursor);
            customCursor = NULL;
        }

        customCursor = SDL_CreateColorCursor(cursorSurface, cursorSurface->w / 2, cursorSurface->h / 2);

        SDL_FreeSurface(cursorSurface);

        SDL_SetCursor(customCursor);
    }

    const graphics::Texture &Skin::getTexture(uint8_t texNum) const
    {
        if(texNum >= MAX_TEX_COUNT)
        {
            OXU_LOG_WARN("Tried to access a non existent texture, returned last texture in array!");
            return textures[MAX_TEX_COUNT - 1];
        }

        return textures[texNum];
    }
}
