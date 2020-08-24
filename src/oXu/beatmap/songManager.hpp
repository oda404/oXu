#pragma once

#include<vector>

#include<oXu/beatmap/song.hpp>

namespace oxu
{
    class SongManager
    {
    private:
        std::vector<Song> songs;

        Song *currentSong = NULL;
        Beatmap *currentBeatmap = NULL;

    public:
        void enumerateSongs();

        void setCurrentSong(size_t index);
        void setCurrentBeatmap(size_t index);

        Song *getCurrentSong();
        Beatmap *getCurrentBeatmap();

        Song *getSong(const size_t &index);
        size_t getSongsSize();
    };
}