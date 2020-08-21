#pragma once

#include<vector>

#include<oXu/beatmap/song.hpp>

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