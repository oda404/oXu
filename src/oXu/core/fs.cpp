#include"fs.hpp"

#include<oXu/core/logger.hpp>
#include<filesystem>

#if defined(__linux__)
#include<pwd.h>
#include<unistd.h>
#elif defined(_WIN32)
    ain t happening buckaroo
#endif // __linux__

namespace oxu::fs
{
    static std::string songs_dir_cache = "";
    static std::string skins_dir_cache = "";

    static std::string get_current_username()
    {
        passwd *pw = getpwuid(getuid());
        if(pw != nullptr)
        {
            return pw->pw_name;
        }

        OXU_LOG_WARN("Couldn't get the current username");
        return "";
    }

    /* If no argument is provided it will default to /home/$USER/.config/oxu/songs */
    void set_songs_dir(const char *p_songs_dir_p)
    {
        if(p_songs_dir_p == nullptr)
        {
            songs_dir_cache = "/home/" + get_current_username() + "/.config/oxu/songs";
        }
        else
        {
            songs_dir_cache = p_songs_dir_p;
        }
    }

    /* If no argument is provided it will default to /home/$USER/.config/oxu/skins */
    void set_skins_dir(const char *p_skins_dir_p)
    {
        if(p_skins_dir_p == nullptr)
        {
            skins_dir_cache = "/home/" + get_current_username() + "/.config/oxu/skins";
        }
        else
        {
            skins_dir_cache = p_skins_dir_p;
        }
    }

    std::string get_skins_dir()
    {
        return skins_dir_cache;
    }

    std::string get_songs_dir()
    {
        return songs_dir_cache;
    }

    namespace stdfs = std::filesystem;

    bool are_user_dirs_valid()
    {
        if(!stdfs::exists(songs_dir_cache)) return false;
        if(!stdfs::exists(skins_dir_cache)) return false;

        return true;
    }

    void validate_user_dirs()
    {
        stdfs::create_directories(songs_dir_cache);
        stdfs::create_directories(skins_dir_cache);
    }
}
