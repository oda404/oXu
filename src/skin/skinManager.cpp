// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.


#include<filesystem>
#include<oxu/skin/skinManager.hpp>
#include<oxu/core/logger.hpp>

namespace oxu
{
    SkinManager::SkinManager(const std::string &config_dir_path):
    m_skins_dir_path(
        std::filesystem::path(config_dir_path) / "skins"
    )
    {

    }

    void SkinManager::enumerateSkins()
    {
        namespace fs = std::filesystem;

        m_skins.clear();

        for(auto &entry: fs::directory_iterator(m_skins_dir_path))
        {
            if(fs::is_directory(entry))
            {
                m_skins.emplace_back(entry.path().string());
            }
        }

        if(m_skins.size() == 0)
        {
            OXU_LOG_WARN("No skins were found in {}", m_skins_dir_path);
        }
    }

    void SkinManager::setCurrentSkin(const size_t &index)
    {
        m_currentSkin = getSkin(index);
        if(m_currentSkin == nullptr)
        {
            OXU_LOG_WARN("Tried to set currentSkin to index {}, is null", index);
        }
    }

    Skin *SkinManager::getCurrentSkin() const
    {
        return m_currentSkin;
    }
    
    Skin *SkinManager::getSkin(const std::size_t &index)
    {
        if(m_skins.size() == 0)
        {
            return nullptr;
        }

        return &m_skins[std::min(index, m_skins.size() - 1)];
    }

    std::size_t SkinManager::getSkinsCount() const
    {
        return m_skins.size();
    }
}
