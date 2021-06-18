// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<vector>
#include<string>
#include<oxu/skin/skin.hpp>

namespace oxu
{
    class SkinManager
    {
    private:
        std::vector<Skin> m_skins;
        Skin *m_currentSkin = nullptr;
        const std::string m_skins_dir_path;

    public:
        SkinManager(const std::string &config_dir_path);
        void enumerateSkins();
        void setCurrentSkin(const size_t &index);
        Skin *getCurrentSkin() const;
        Skin *getSkin(const std::size_t &index);
        std::size_t getSkinsCount() const;
    };
}