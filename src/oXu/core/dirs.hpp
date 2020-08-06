#pragma once

#include<string>

#ifdef __linux__
#include<pwd.h>
#include<unistd.h>
#endif // __linux__

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
