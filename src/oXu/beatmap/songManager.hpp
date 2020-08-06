#pragma once

#include<string>
#include<vector>
#include<filesystem>

#include<unistd.h>
#include<pwd.h>

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

        Song &getSong(const size_t &index);
        size_t getSongsSize();
    };
}