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
    Skin *m_current_skin = nullptr;
    std::string m_skins_dir;

public:
    SkinManager(const std::string &skins_dir);
    /**
     * Sets the skins directory path. Also clears any previously enumerated skins. 
     */
    void set_skins_dir(const std::string &skins_dir);
    /**
     * Gets the skins directory path.
     */
    std::string get_skins_dir() const;
    /**
     *  Enumerates and registers all of the skins in the skins directory.
     */
    bool enumerate_skins();
    /**
     * Sets the current skin.
     */
    bool set_current_skin(const size_t &index);
    bool set_current_skin(const std::string &name);
    /**
     * Gets the current skin.
    */
    Skin *get_current_skin() const;

    Skin *get_skin(const std::size_t &index);
    Skin *get_skin(const std::string &name);
    
    std::size_t get_skins_count() const;
};

}
