// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"skinManager.hpp"

void oxu::SkinManager::enumSkins()
{
    const char *path = "skins/";
    for(auto &p: fs::directory_iterator(path))
    {
        if(fs::is_directory(p))
        {
            skins.emplace_back(p.path());
        }
    }
}

const std::string &oxu::SkinManager::getSkinPath(const int &index)
{
    return skins[index];
}