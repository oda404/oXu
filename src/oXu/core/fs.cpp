#include"fs.hpp"

#include<oXu/core/logger.hpp>

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

    /* If no argument is provided it will default to /home/$USER/.config/oXu/songs */
    void set_songs_dir(const char *p_songs_dir_p)
    {
        if(p_songs_dir_p == nullptr)
        {
            songs_dir_cache = "/home/" + get_current_username() + "/.config/oXu/songs";
        }
        else
        {
            songs_dir_cache = p_songs_dir_p;
        }
    }

    /* If no argument is provided it will default to /home/$USER/.config/oXu/skins */
    void set_skins_dir(const char *p_skins_dir_p)
    {
        if(p_skins_dir_p == nullptr)
        {
            skins_dir_cache = "/home/" + get_current_username() + "/.config/oXu/skins";
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

    bool are_user_dirs_valid()
    {

    }

    void validate_user_dirs()
    {

    }
}
