#pragma once

#include<string>
#include<vector>

namespace oxu
{
    enum class MetadataField
    {
        TITLE = 0,
        TITLE_UNICODE = 1,
        ARTIST = 2,
        ARTIST_UNICODE = 3,
        CREATOR = 4,
        VERSION = 5,
        SOURCE = 6,
        TAGS = 7,
        BEATMAP_ID = 8,
        BEATMAP_SET_ID = 9,
        INVALID = 255
    };

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
