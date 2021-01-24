#pragma once

#include<string>

namespace oxu::fs
{
    void set_songs_dir(const char *p_songs_dir_p = nullptr);
    void set_skins_dir(const char *p_skins_dir_p = nullptr);
    std::string get_songs_dir();
    std::string get_skins_dir();
    bool are_user_dirs_valid();
    void validate_user_dirs();
}
