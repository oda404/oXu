// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"skinManager.hpp"

#include<filesystem>

#include<oXu/utils/logger.hpp>
#include<oXu/core/dirs.hpp>

namespace oxu
{
    void SkinManager::enumerateSkins()
    {
        namespace fs = std::filesystem;

        skins.clear();

        for(const fs::directory_entry &entry: fs::directory_iterator(Dirs::skins))
        {
            if(fs::is_directory(entry))
            {
                skins.emplace_back(entry.path().string());
            }
        }

        if(skins.size() == 0)
        {
            LOG_ERR("No skins were found in {}", Dirs::skins);
        }
    }

    void SkinManager::setCurrentSkin(const size_t &index)
    {
        currentSkin = getSkin(index);
        if(currentSkin == NULL)
        {
            LOG_WARN("SkinManager::setCurrentSkin({}): See above warning ^", index);
        }
    }

    Skin *SkinManager::getCurrentSkin()
    {
        return currentSkin;
    }
    
    Skin *SkinManager::getSkin(const std::size_t &index)
    {
        if(skins.size() == 0)
        {
            LOG_WARN("SkinManager::getSkin({}): No skins were found, returned NULL!", index);
            return NULL;
        }
        else if(index >= skins.size())
        {
            //TODO: check if there are any skins at all in the vector
            LOG_WARN("SkinManager::getSkin({}): Tried to access a non extistent skin, returned last skin in vector!", index);
            return &skins[skins.size() - 1];
        }

        return &skins[index];
    }

    std::size_t SkinManager::getSkinsSize()
    {
        return skins.size();
    }
}
