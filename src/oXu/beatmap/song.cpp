#include "song.hpp"

namespace oxu
{
    Song::Song(const std::string &name_p, const std::string &path_p):
    name(name_p), path(path_p)
    {
        LOG_DEBUG("Loaded song {0}", name);
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
    }

    Beatmap &Song::getBeatmap(size_t index)
    {
        if(index > beatmaps.size() - 1)
        {
            LOG_DEBUG("Tried to access a non existent beatmap, returned last beatmap in vector");
            beatmaps[beatmaps.size() - 1];
        }

        return beatmaps[index];
    }

    int Song::getBetmapsNumber()
    {
        return beatmaps.size();
    }
}