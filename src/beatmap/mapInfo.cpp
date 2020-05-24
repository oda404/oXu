// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"mapInfo.hpp"

namespace oxu
{
    void MapInfo::clear()
    {
        mapGeneral.clear();
        mapDifficulty.clear();
        mapMetadata.clear();
    }

    void MapInfo::addGeneralAttr(const std::string &key, const std::string &attr)
    {
        mapGeneral.emplace(key, attr);
    }

    void MapInfo::addDifficultyAttr(const std::string &key, const float &attr)
    {
        mapDifficulty.emplace(key, attr);
    }

    void MapInfo::addMetadataAttr(const std::string &key, const std::string &attr)
    {
        mapMetadata.emplace(key, attr);
    }
}