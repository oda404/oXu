
#pragma once
#include<string>
#include<oxu/framework/utils/vector2.hpp>

namespace oxu
{

    struct Config
    {
        std::string configDirPath;
        framework::Vector2<std::uint16_t> screenSize;
    };

    /* Sets up stuff idk */
    bool init(const Config &config);
}
