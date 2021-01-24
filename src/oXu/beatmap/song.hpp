#pragma once

#include<string>
#include<vector>

#include<oXu/beatmap/beatmap.hpp>

namespace oxu
{

    class Song
    {
    private:
        std::vector<Beatmap> m_beatmaps;

    public:
        std::string m_path;
        std::string m_name;

        Song(const std::string &path);

        void enumerateBeatmaps();

        Beatmap *getBeatmap(const size_t &index);
        size_t getBeatmapsCount() const;
    };

}
