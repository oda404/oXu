#pragma once

#include<string>
#include<vector>
#include<filesystem>

#include<oXu/utils/logger.hpp>
#include<oXu/beatmap/song.hpp>

namespace oxu
{
    class SongManager
    {
    private:
        std::vector<Song> songs;

    public:
        void enumerateSongs();

        Song &getSong(size_t index);
        int getSongsNumber();
    };
}