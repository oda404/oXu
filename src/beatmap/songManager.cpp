
#include<filesystem>
#include<oxu/beatmap/songManager.hpp>
#include<oxu/framework/logger.hpp>

namespace oxu
{

using namespace framework;

SongManager::SongManager(
    const std::string &songs_dir
)
{
    set_songs_dir(songs_dir);
}

void SongManager::set_songs_dir(const std::string &path)
{
    m_songs_dir = path;
}

std::string SongManager::get_songs_dir() const
{
    return m_songs_dir;
}

bool SongManager::enumerate_songs()
{
    namespace fs = std::filesystem;

    m_songs.clear();

    for(auto &entry: fs::directory_iterator(m_songs_dir))
    {
        if(fs::is_directory(entry))
        {
            m_songs.emplace_back(entry.path());
        }
    }

    if(!m_songs.size())
    {
        OXU_LOG_WARN("No songs were found in {}", m_songs_dir);
        return false;
    }

    return true;
}

bool SongManager::set_current_song(std::size_t index)
{
    m_currentSong = get_song(index);
    if(m_currentSong == nullptr)
    {
        return false;
    }
    return true;
}

bool SongManager::set_current_beatmap(std::size_t index)
{
    if(m_currentSong == nullptr)
    {
        m_currentBeatmap = nullptr;
        return false;
    }

    m_currentBeatmap = m_currentSong->getBeatmap(index);
    if(!m_currentBeatmap)
    {
        return false;
    }

    return true;
}

Song *SongManager::get_current_song() const
{
    return m_currentSong;
}

Beatmap *SongManager::get_current_beatmap() const
{
    return m_currentBeatmap;
}

Song *SongManager::get_song(size_t index)
{
    if(!m_songs.size())
    {
        return nullptr;
    }

    return &m_songs[std::min(index, m_songs.size() -1)];
}

std::size_t SongManager::get_songs_count() const
{
    return m_songs.size();
}

}
