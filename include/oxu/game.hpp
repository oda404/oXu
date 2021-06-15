#pragma once
#include<string>
#include<cstdint>
#include<oxu/utils/vector2.hpp>

namespace oxu
{
    struct Config
    {
        std::string configDirPath;
        Vector2<std::uint16_t> screenSize;
    };

    /* Sets up stuff idk */
    bool init(const Config &config);
}
