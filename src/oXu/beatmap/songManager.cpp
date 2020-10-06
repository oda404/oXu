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

        if(songs.size() == 0)
        {
            OXU_LOG_WARN("No songs were found in {}", Dirs::songs);
        }
    }

    void SongManager::setCurrentSong(std::size_t index)
    {
        currentSong = getSong(index);
        if(currentSong == NULL)
        {
            OXU_LOG_WARN_EXT("Can't set currentSong (NULL)");
            currentSong = NULL;
        }
    }

    void SongManager::setCurrentBeatmap(std::size_t index)
    {
        if(currentSong == NULL)
        {
            OXU_LOG_WARN_EXT("currentSong is NULL, currentBeatmap will also be NULL!");
            currentBeatmap = NULL;
        }
        else
        {
            currentBeatmap = currentSong->getBeatmap(index);
        }
    }

    Song *SongManager::getCurrentSong()
    {
        return currentSong;
    }

    Beatmap *SongManager::getCurrentBeatmap()
    {
        return currentBeatmap;
    }

    Song *SongManager::getSong(const size_t &index)
    {
        if(songs.size() == 0)
        {
            OXU_LOG_WARN("SongManager::getSong({}): No songs were found, returned NULL!", index);
            return NULL;
        }
        else if(index >= songs.size())
        {
            OXU_LOG_WARN("SongManager::getSong({}): Tried to access a non existent song, returned last song in vector!", index);
            return &songs[songs.size() - 1];
        }

        return &songs[index];
    }

    std::size_t SongManager::getSongsSize()
    {
        return songs.size();
    }
}
