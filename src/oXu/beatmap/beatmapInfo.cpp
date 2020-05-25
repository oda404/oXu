// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"beatmapInfo.hpp"

namespace oxu
{
    void BeatmapInfo::clear()
    {
        mapGeneral.clear();
        mapDifficulty.clear();
        mapMetadata.clear();
    }

    void BeatmapInfo::addGeneralAttr(const std::string &key, const std::string &attr)
    {
        mapGeneral.emplace(key, attr);
    }

    void BeatmapInfo::addDifficultyAttr(const std::string &key, const float &attr)
    {
        mapDifficulty.emplace(key, attr);
    }

    void BeatmapInfo::addMetadataAttr(const std::string &key, const std::string &attr)
    {
        mapMetadata.emplace(key, attr);
    }
}