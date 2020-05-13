// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

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