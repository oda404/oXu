#pragma once

#include<vector>

#include<oXu/beatmap/song.hpp>

namespace oxu
{
    class SongManager
    {
    private:
        std::vector<Song> m_songs;

        Song *m_currentSong = nullptr;
        Beatmap *m_currentBeatmap = nullptr;

    public:
        void enumerateSongs();

        void setCurrentSong(size_t index);
        void setCurrentBeatmap(size_t index);

        Song *getCurrentSong() const;
        Beatmap *getCurrentBeatmap() const;

        Song *getSong(const size_t &index);
        size_t getSongsSize() const;
    };
}
