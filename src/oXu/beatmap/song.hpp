#pragma once

#include<filesystem>
#include<vector>

#include<oXu/utils/logger.hpp>
#include<oXu/beatmap/beatmap.hpp>

namespace oxu
{

    class Song
    {
    private:
        std::vector<Beatmap> beatmaps;

    public:
        std::string path;
        std::string name;

        Song(const std::string &path_p);

        void enumerateBeatmaps();

        Beatmap &getBeatmap(const size_t &index);

        size_t getBetmapsNumber();
    };

}
