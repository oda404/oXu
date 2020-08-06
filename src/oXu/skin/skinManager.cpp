// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"skinManager.hpp"

namespace oxu
{
    void SkinManager::enumerateSkins()
    {
        namespace fs = std::filesystem;

        for(const fs::directory_entry &entry: fs::directory_iterator(Dirs::skins))
        {
            if(fs::is_directory(entry))
            {
                std::string path = entry.path().string();
                skins.emplace_back(path);
            }
        }
    }

    Skin &SkinManager::getSkin(const std::size_t &index)
    {
        if(index > skins.size() - 1)
        {
            //TODO: check if there are any skins at all in the vector
            LOG_WARN("Tried to access a non extistent skin, returned last skin in vector");
            return skins[skins.size() - 1];
        }

        return skins[index];
    }

    std::size_t SkinManager::getSkinsSize()
    {
        return skins.size();
    }
}
