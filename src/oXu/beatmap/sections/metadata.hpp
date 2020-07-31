#pragma once

#include<string>
#include<vector>

namespace oxu
{
    struct Metadata
    {
        std::string title;
        std::string titleUnicode;
        std::string artist;
        std::string artistUnicode;
        std::string creator;
        std::string version;
        std::string source;
        std::vector<std::string> tags;
        int beatmapID;
        int beatmapSetID;
    };
}
