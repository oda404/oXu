
#include<oxu/framework/fs.hpp>
#include<cstdlib>
#include<iostream>
#include<unistd.h>
#include<climits>

namespace oxu::framework::fs
{

std::string path_resolve_homedir(std::string path)
{
    if(!path.size())
        return "";
    
    if(path[0] == '~')
    {
        path.erase(path.begin());
        path = "/home/" + std::string(getlogin()) + path;
    }

    return path;
}

}
