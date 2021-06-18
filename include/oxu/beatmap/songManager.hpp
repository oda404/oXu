#pragma once

#include<vector>
#include<string>
#include<oxu/beatmap/song.hpp>
#include<oxu/framework/window.hpp>

namespace oxu
{
    class SongManager
    {
    private:
        std::vector<Song> m_songs;
        Song *m_currentSong = nullptr;
        Beatmap *m_currentBeatmap = nullptr;
        const std::string m_songs_dir_path;

    public:
        SongManager(
            const std::string &config_dir_path
        );

        void enumerateSongs();

        void setCurrentSong(size_t index);
        void setCurrentBeatmap(size_t index);

        Song *getCurrentSong() const;
        Beatmap *getCurrentBeatmap() const;

        Song *getSong(const size_t &index);
        size_t getSongsSize() const;
    };
}
