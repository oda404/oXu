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
    std::string m_songs_dir;

public:
    SongManager(
        const std::string &songs_dir
    );
    /** 
     * Sets the songs directory. Also clears any previosly enumerated songs. 
     */
    void set_songs_dir(const std::string &path);
    /**
     * Gets the songs directory path.
     */
    std::string get_songs_dir() const;
    /** 
     * Enumeartes and registers all of the songs.
     * @return false if no songs were found, true otherwise. 
     */
    bool enumerate_songs();
    /**
     * Sets the current song.
     * @return true if succesfull, false if index doesn't exist.
     */
    bool set_current_song(size_t index);
    /**
     * Sets the current song.
     * @return true if succesull, false if name doesn't exist.
     */
    bool set_current_song(const std::string &name);
    /**
     * Sets the current beatmap of the current song.
     * @return true if successfull, false if either index was not found or current_song was not set.
     */
    bool set_current_beatmap(size_t index);

    Song *get_current_song() const;
    Beatmap *get_current_beatmap() const;

    Song *get_song(size_t index);
    size_t get_songs_count() const;
};

}
