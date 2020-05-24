// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<string>
#include<vector>
#include<map>

namespace oxu
{
    struct MapInfo
    {
    private:
        std::map<std::string, std::string> mapGeneral;
        std::map<std::string, float>       mapDifficulty;
        std::map<std::string, std::string> mapMetadata;

    public:
        float ARInSeconds;
        void clear();

        void addGeneralAttr(const std::string &key, const std::string &attr);
        void addDifficultyAttr(const std::string &key, const float &attr);
        void addMetadataAttr(const std::string &key, const std::string &attr);

        inline const std::string &getGeneralAttr(const char *attr) { return mapGeneral.find(attr)->second; }
        inline const float &getDifficultyAttr(const char *attr) { return mapDifficulty.find(attr)->second; }
        inline const std::string &getMetadatAttr(const char *attr) { return mapMetadata.find(attr)->second; }
    };
}
