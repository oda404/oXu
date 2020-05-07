#include"mapInfo.hpp"

oxu::MapInfo::MapInfo()
{
    
}

void oxu::MapInfo::clear()
{

}

oxu::MapInfo &oxu::MapInfo::getInstance()
{
    static MapInfo instance;
    return instance;
}