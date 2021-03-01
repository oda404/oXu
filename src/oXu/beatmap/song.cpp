#include "song.hpp"

#include<filesystem>

#include<oXu/core/logger.hpp>

namespace oxu
{
    Song::Song(
        const window::Window &window,
        const std::string &path
    ):
    m_path(path), 
    m_name(path.substr(path.find_last_of('/') + 1, path.size() - 1)),
    mr_window(window)
    {
        OXU_LOG_DEBUG("Found song {}", m_name);
        enumerateBeatmaps();
    }

    void Song::enumerateBeatmaps()
    {
        namespace fs = std::filesystem;

        m_beatmaps.clear();

        for(auto &entry: fs::directory_iterator(m_path))
        {
            if(entry.path().extension() == ".osu")
            {
                m_beatmaps.emplace_back(entry.path());
            }
        }

        if(m_beatmaps.size() == 0)
        {
            OXU_LOG_WARN("No .osu files were found in song {}", m_path);
        }
    }

    Beatmap *Song::getBeatmap(const size_t &index)
    {
        if(m_beatmaps.size() == 0)
        {
            return nullptr;
        }

        return &m_beatmaps[std::min(index, m_beatmaps.size() - 1)];
    }

    size_t Song::getBeatmapsCount() const
    {
        return m_beatmaps.size();
    }
}