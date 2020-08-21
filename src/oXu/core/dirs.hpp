#pragma once

#include<string>

namespace oxu
{
    struct Dirs
    {
        static std::string skins;
        static std::string songs;
        static std::string res;
        static std::string oxu;

        static void setDirs();
    };
}
