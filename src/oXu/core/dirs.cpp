#include"dirs.hpp"

#ifdef __linux__
#include<pwd.h>
#include<unistd.h>
#endif // __linux__

namespace oxu
{
    std::string Dirs::skins = "";
    std::string Dirs::songs = "";
    std::string Dirs::res = "";
    std::string Dirs::oxu = "";

    void Dirs::setDirs()
    {
    #ifdef __linux__
        passwd *pw = getpwuid(getuid());
        oxu = "/home/" + std::string(pw->pw_name) + "/.config/oXu";
        skins = oxu + "/skins";
        songs = oxu + "/songs";
        res = oxu + "/res";  
    #elif _WIN32
        //TODO
    #endif // __linux__
    }
}