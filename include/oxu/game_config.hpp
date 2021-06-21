
#pragma once

#include<string>
#include<oxu/framework/utils/vector2.hpp>

namespace oxu
{

struct GameConfig
{
    static constexpr framework::Vector2<std::uint16_t> 
    default_window_size = { 800, 600 };

    static constexpr std::string_view
    default_res_dir = "~/.config/oxu/res";

    static constexpr std::string_view
    default_songs_dir = "~/.config/oxu/songs";

    static constexpr std::string_view
    default_skins_dir = "~/.config/oxu/skins";

    std::string res_dir;
    std::string songs_dir;
    std::string skins_dir;
    framework::Vector2<std::uint16_t> window_size;
};

}
