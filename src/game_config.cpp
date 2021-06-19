
#include<oxu/game_config.hpp>
#include<oxu/framework/utils/vector2.hpp>
#include<cstdint>

namespace oxu
{

const framework::Vector2<std::uint16_t> 
GameConfig::DEFAULT_WINDOW_SIZE = { 800, 600 };

const std::string 
GameConfig::DEFAULT_RESOURCES_DIR = "~/.config/oxu/res";

const std::string
GameConfig::DEFAULT_SKINS_DIR = "~/.config/oxu/skins";

const std::string 
GameConfig::DEFAULT_SONGS_DIR = "~/.config/oxu/songs";

}
