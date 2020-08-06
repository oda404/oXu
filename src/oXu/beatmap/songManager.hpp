#pragma once

#include<string>
#include<vector>
#include<filesystem>

#include<oXu/utils/logger.hpp>
#include<oXu/beatmap/song.hpp>
#include<oXu/core/dirs.hpp>

namespace oxu
{
    class SongManager
    {
    private:
        std::vector<Song> songs;

    public:
        void enumerateSongs();

        Song &getSong(const size_t &index);
        size_t getSongsSize();
    };
}