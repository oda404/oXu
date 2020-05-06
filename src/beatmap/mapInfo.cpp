#include"mapInfo.hpp"

oxu::MapInfo::MapInfo()
{
    
}

void oxu::MapInfo::clearMap()
{

}

oxu::MapInfo &oxu::MapInfo::getInstance()
{
    static MapInfo instance;
    return instance;
}