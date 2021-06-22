// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.


#include<filesystem>
#include<oxu/skin/skinManager.hpp>
#include<oxu/framework/logger.hpp>

namespace oxu
{
using namespace framework;

SkinManager::SkinManager(const std::string &skins_dir)
{
    set_skins_dir(skins_dir);
}

void SkinManager::set_skins_dir(const std::string &skins_dir)
{
    m_skins_dir = skins_dir;
}

std::string SkinManager::get_skins_dir() const
{
    return m_skins_dir;
}

bool SkinManager::enumerate_skins()
{
    namespace fs = std::filesystem;

    m_skins.clear();

    for(auto &entry: fs::directory_iterator(m_skins_dir))
    {
        if(fs::is_directory(entry))
        {
            m_skins.emplace_back(entry.path().string());
        }
    }

    if(m_skins.size() == 0)
    {
        OXU_LOG_WARN("No skins were found in {}", m_skins_dir);
        return false;
    }

    return true;
}

bool SkinManager::set_current_skin(const size_t &index)
{
    m_current_skin = get_skin(index);
    if(!m_current_skin)
        return false;

    return true;
}

bool SkinManager::set_current_skin(const std::string &name)
{
    m_current_skin = get_skin(name);
    if(!m_current_skin)
        return false;

    return true;
}

Skin *SkinManager::get_current_skin() const
{
    return m_current_skin;
}

Skin *SkinManager::get_skin(const std::size_t &index)
{
    if(m_skins.size() == 0)
        return nullptr;

    return &m_skins[std::min(index, m_skins.size() - 1)];
}

Skin *SkinManager::get_skin(const std::string &name)
{
    for(auto &skin: m_skins)
    {
        if(skin.get_name() == name)
            return &skin;
    }

    return nullptr;
}

std::size_t SkinManager::get_skins_count() const
{
    return m_skins.size();
}

}
