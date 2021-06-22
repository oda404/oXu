
#include<oxu/framework/fs.hpp>
#include<filesystem>
#include<cstdlib>
#include<iostream>
#include<unistd.h>
#include<climits>

namespace oxu::framework::fs
{

namespace stdfs = std::filesystem;

std::string canonical(std::string path)
{
    if(!path.size())
        return "";
    
    if(path[0] == '~')
    {
        path.erase(path.begin());
        path = "/home/" + std::string(getlogin()) + path;
    }

    path = stdfs::weakly_canonical(path);

    return path;
}

bool dir_create(const std::string &path)
{
    if(!stdfs::exists(path))
    {
        try
        {
            stdfs::create_directory(path);
        }
        catch(...)
        {
            return false;
        }
    }

    return true;
}

}
