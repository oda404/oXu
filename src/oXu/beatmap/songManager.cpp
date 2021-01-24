#include"songManager.hpp"

#include<filesystem>

#include<oXu/core/fs.hpp>
#include<oXu/core/logger.hpp>

namespace oxu
{
    void SongManager::enumerateSongs()
    {
        namespace fs = std::filesystem;
        namespace oxufs = oxu::fs;

        m_songs.clear();

        for(auto &entry: fs::directory_iterator(oxufs::get_songs_dir()))
        {
            if(fs::is_directory(entry))
            {
                m_songs.emplace_back(entry.path());
            }
        }

        if(m_songs.size() == 0)
        {
            OXU_LOG_WARN("No songs were found in {}", oxufs::get_songs_dir());
        }
    }

    void SongManager::setCurrentSong(std::size_t index)
    {
        m_currentSong = getSong(index);
        if(m_currentSong == nullptr)
        {
            OXU_LOG_WARN("Tried to set currentSong to index {}, is null", index);
        }
    }

    void SongManager::setCurrentBeatmap(std::size_t index)
    {
        if(m_currentSong == nullptr)
        {
            OXU_LOG_WARN("Tried to set currentBeatmap but currentSong is null");
            m_currentBeatmap = nullptr;
        }
        else
        {
            m_currentBeatmap = m_currentSong->getBeatmap(index);
        }
    }

    Song *SongManager::getCurrentSong() const
    {
        return m_currentSong;
    }

    Beatmap *SongManager::getCurrentBeatmap() const
    {
        return m_currentBeatmap;
    }

    Song *SongManager::getSong(const size_t &index)
    {
        if(m_songs.size() == 0)
        {
            return nullptr;
        }

        return &m_songs[std::min(index, m_songs.size() -1)];
    }

    std::size_t SongManager::getSongsSize() const
    {
        return m_songs.size();
    }
}
