
#pragma once

#include<string>
#include<oxu/framework/utils/vector2.hpp>

namespace oxu
{

struct GameConfig
{
    static const framework::Vector2<std::uint16_t> 
    DEFAULT_WINDOW_SIZE;

    static const std::string 
    DEFAULT_RESOURCES_DIR;

    static const std::string 
    DEFAULT_SONGS_DIR;

    static const std::string 
    DEFAULT_SKINS_DIR;

    std::string resources_dir;
    std::string songs_dir;
    std::string skins_dir;
    framework::Vector2<std::uint16_t> window_size;
};

}
