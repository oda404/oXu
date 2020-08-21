#include"songManager.hpp"

#include<filesystem>

#include<oXu/core/dirs.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    void SongManager::enumerateSongs()
    {
        namespace fs = std::filesystem;

        songs.clear();

        for(auto &entry: fs::directory_iterator(Dirs::songs))
        {
            if(fs::is_directory(entry))
            {
                songs.emplace_back(entry.path());
            }
        }
    }

    Song &SongManager::getSong(const size_t &index)
    {
        if(index > songs.size() - 1)
        {
            LOG_DEBUG("Tried to access a non extistent song, returned last song in vector");
            return songs[songs.size() - 1];
        }

        return songs[index];
    }

    std::size_t SongManager::getSongsSize()
    {
        return songs.size();
    }
}