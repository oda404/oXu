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
        std::string name;
        std::string path;

        Song(const std::string &name_p, const std::string &path_p);

        void enumerateBeatmaps();

        Beatmap &getBeatmap(size_t index);

        int getBetmapsNumber();
    };

}
