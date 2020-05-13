#include"skinManager.hpp"

void oxu::SkinManager::enumSkins()
{
    const char *path = "skins/";
    for(auto &p: fs::directory_iterator(path))
    {
        if(fs::is_directory(p))
        {
            skins.emplace_back(p.path());
        }
    }
}

const std::string &oxu::SkinManager::getSkinPath(const int &index)
{
    return skins[index];
}