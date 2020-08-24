// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<vector>

#include<oXu/skin/skin.hpp>

namespace oxu
{
    class SkinManager
    {
    private:
        std::vector<Skin> skins;

        Skin *currentSkin = NULL;

    public:
        void enumerateSkins();

        void setCurrentSkin(const size_t &index);

        Skin *getCurrentSkin();

        Skin *getSkin(const std::size_t &index);
        std::size_t getSkinsSize();
    };
}