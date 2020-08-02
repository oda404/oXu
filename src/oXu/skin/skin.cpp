#include"skin.hpp"

namespace oxu
{
    Skin::Skin(const std::string &path_p, const std::string &name_p):
    path(path_p), name(name_p)
    {
        
    }

    Skin::~Skin()
    {
        if(texturesAreAllocated)
        {
            unloadTextures();
        }
    }

    void Skin::parseAndLoadTexture(const std::string &path, SDL_Renderer *targetRenderer)
    {
        std::string name = path.substr(path.find_last_of('/') + 1, path.size() - 1);

        std::map<std::string, std::uint8_t>::const_iterator pair = texNamesMap.find(name);

        if(pair->first != "")
        {
            textures[pair->second] = IMG_LoadTexture(targetRenderer, path.c_str());
        }
    }

    void Skin::loadTextures(SDL_Renderer *renderer)
    {
        if(texturesAreAllocated)
        {
            unloadTextures();
        }

        textures = new SDL_Texture*[MAX_TEX_COUNT]{NULL};
        texturesAreAllocated = true;

        namespace fs = std::filesystem;

        for(const fs::directory_entry &entry: fs::directory_iterator(path))
        {
            if(entry.path().extension() == ".png")
            {
                parseAndLoadTexture(entry.path(), renderer);
            }
        }
    }

    void Skin::unloadTextures()
    {
        for(uint8_t i = 0; i < MAX_TEX_COUNT; ++i)
        {
            SDL_DestroyTexture(textures[i]);
        }

        delete[] textures;
    }

    void Skin::setCursor()
    {
        SDL_Surface *cursorSurface = IMG_Load((path + "/cursor.png").c_str());
        if(!cursorSurface)
        {
            LOG_WARN(IMG_GetError());
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

    SDL_Texture *Skin::getTexture(uint8_t texNum)
    {
        if(texNum >= MAX_TEX_COUNT)
        {
            LOG_WARN("Tried to access a non existent texture, returned last texture in array!");
            return textures[MAX_TEX_COUNT - 1];
        }

        return textures[texNum];
    }
}
