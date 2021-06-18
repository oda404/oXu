#pragma once

#include<string>
#include<vector>
#include<oxu/beatmap/beatmap.hpp>
#include<oxu/framework/window.hpp>

namespace oxu
{

    class Song
    {
    private:
        std::vector<Beatmap> m_beatmaps;
        std::string m_path;
        std::string m_name;

    public:
        Song(
            const std::string &path
        );

        void enumerateBeatmaps();

        Beatmap *getBeatmap(const size_t &index);
        size_t getBeatmapsCount() const;
    };

}
