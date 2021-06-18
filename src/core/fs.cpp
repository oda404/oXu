
#include<oxu/core/fs.hpp>
#include<oxu/framework/logger.hpp>
#include<filesystem>

#if defined(__linux__)
#include<pwd.h>
#include<unistd.h>
#elif defined(_WIN32)
    ain t happening buckaroo
#endif // __linux__

namespace oxu::fs
{
    namespace stdfs = std::filesystem;

    bool is_config_dir_valid(const std::string &path)
    {
        const std::string skins_dir_path = 
        stdfs::path(path) / "skins";
        const std::string songs_dir_path = 
        stdfs::path(path) / "songs";

        if(!stdfs::exists(skins_dir_path)) return false;
        if(!stdfs::exists(songs_dir_path)) return false;

        return true;
    }

    void validate_config_dir(const std::string &path)
    {
        const std::string skins_dir_path = 
        stdfs::path(path) / "skins";
        const std::string songs_dir_path = 
        stdfs::path(path) / "songs";

        stdfs::create_directories(skins_dir_path);
        stdfs::create_directories(songs_dir_path);
    }
}
