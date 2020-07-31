#include"songManager.hpp"

namespace oxu
{
    static std::string getSongName(const std::string &dirPath)
    {
        std::string dirName;

        dirName = dirPath.substr(0, dirName.find_last_of("/\\"));

        return dirName.substr(dirName.find_first_of(' ') + 1, dirName.size() - 1);
    }

    void SongManager::enumerateSongs()
    {
        namespace fs = std::filesystem;

        songs.clear();

        for(auto &entry: fs::directory_iterator("songs/"))
        {
            if(fs::is_directory(entry))
            {
                songs.emplace_back(getSongName(entry.path()), entry.path());
            }
        }
    }

    Song &SongManager::getSong(size_t index)
    {
        if(index > songs.size() - 1)
        {
            LOG_DEBUG("Tried to access a non extistent song, returned last song in vector");
            return songs[songs.size() - 1];
        }

        return songs[index];
    }

    int SongManager::getSongsNumber()
    {
        return songs.size();
    }
}