#pragma once

#include<string>
#include<vector>
#include<oxu/beatmap/beatmap.hpp>
#include<oxu/core/window.hpp>

namespace oxu
{

    class Song
    {
    private:
        std::vector<Beatmap> m_beatmaps;
        std::string m_path;
        std::string m_name;
        const window::Window &mr_window;

    public:
        Song(
            const window::Window &window,
            const std::string &path
        );

        void enumerateBeatmaps();

        Beatmap *getBeatmap(const size_t &index);
        size_t getBeatmapsCount() const;
    };

}
