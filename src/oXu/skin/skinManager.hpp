// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_image.h>

#include<filesystem>
#include<vector>
#include<string>

#include<pwd.h>
#include<unistd.h>

#include<oXu/skin/skin.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    class SkinManager
    {
    private:
        std::vector<Skin> skins;

    public:
        void enumerateSkins();

        Skin &getSkin(const std::size_t &index);
        std::size_t getSkinsSize();
    };
}