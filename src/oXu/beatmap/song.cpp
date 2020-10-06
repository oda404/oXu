#include "song.hpp"

#include<filesystem>

#include<oXu/utils/logger.hpp>

namespace oxu
{
    Song::Song(const std::string &path_p):
    path(path_p), name(path_p.substr(path_p.find_last_of('/') + 1, path_p.size() - 1))
    {
        OXU_LOG_DEBUG("Found song {}", name);
        enumerateBeatmaps();
    }

    void Song::enumerateBeatmaps()
    {
        namespace fs = std::filesystem;

        beatmaps.clear();

        for(auto &entry: fs::directory_iterator(path))
        {
            if(entry.path().extension() == ".osu")
            {
                beatmaps.emplace_back(entry.path());
            }
        }

        if(beatmaps.size() == 0)
        {
            OXU_LOG_WARN("No .osu files (beatmaps) were found in {}", path);
        }
    }

    Beatmap *Song::getBeatmap(const size_t &index)
    {
        if(beatmaps.size() == 0)
        {
            OXU_LOG_WARN_EXT("No beatmaps were found, returned NULL!");
            return NULL;
        }
        else if(index >= beatmaps.size())
        {
            OXU_LOG_WARN_EXT("Tried to access a non existent beatmap, returned last beatmap in vector!");
            return &beatmaps[beatmaps.size() - 1];
        }

        return &beatmaps[index];
    }

    size_t Song::getBetmapsNumber()
    {
        return beatmaps.size();
    }
}