
#pragma once
#include<string>
#include<oxu/framework/utils/vector2.hpp>

namespace oxu
{

#define DEFAULT_RES_DIR   "/home/" + std::string(getlogin()) + "/.config/oxu/res"
#define DEFAULT_SONGS_DIR "/home/" + std::string(getlogin()) + "/.config/oxu/songs"
#define DEFAULT_SKINS_DIR "/home/" + std::string(getlogin()) + "/.config/oxu/skins"
#define DEFAULT_WINDOW_SIZE { 800, 600 }

struct Config
{
    std::string resources_dir_path;
    std::string songs_dir_path;
    std::string skins_dir_path;
    framework::Vector2<std::uint16_t> window_size;
};

/* Starts the game. */
bool init(const Config &config);

}
