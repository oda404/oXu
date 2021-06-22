
#include<SDL2/SDL.h>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/window.hpp>
#include<oxu/framework/graphics/handler.hpp>
#include<oxu/framework/audio/handler.hpp>
#include<oxu/framework/threading/thread.hpp>
#include<oxu/framework/framework.hpp>
#include<oxu/framework/fs.hpp>
#include<oxu/game.hpp>
#include<oxu/skin/skinManager.hpp>
#include<oxu/beatmap/songManager.hpp>

namespace oxu
{

using namespace framework;
using namespace framework::threading;
namespace oxufs = oxu::framework::fs;
namespace stdfs = std::filesystem;

static void game_loop(
    SongManager &song_manager_p,
    SkinManager &skin_manager_p,
    Thread &this_thread_p
)
{
    SDL_Event sdl_event;
    bool window_open = true;
    Beatmap *p_current_beatmap = song_manager_p.get_current_beatmap();
    if(p_current_beatmap)
    {
        p_current_beatmap->start();
    }

    this_thread_p.start();
    while(window_open)
    {
        this_thread_p.cap_fps();

        if(p_current_beatmap)
        {
            p_current_beatmap->updateObjects(this_thread_p.get_delta());
        }

        /* Window event handling */
        while(SDL_PollEvent(&sdl_event))
        {
            switch(sdl_event.type)
            {
            case SDL_QUIT:
                window_open = false;
                break;
            }
        }
    }
}

static void clean()
{
    graphics::handler::shut_down();
    audio::handler::shutDown();
    window::destroy();
    framework::destroy();
}

bool init(const GameConfig &config)
{
    framework::init();

    if(!window::init("oxu", config.window_size))
    {
        return false;
    }

    if(!oxufs::dir_create(config.res_dir))
        OXU_LOG_WARN("Couldn't create [{}] are you privileged ?", config.res_dir);
    if(!oxufs::dir_create(config.skins_dir))
        OXU_LOG_WARN("Couldn't create [{}] are you privileged ?", config.skins_dir);
    if(!oxufs::dir_create(config.songs_dir))
        OXU_LOG_WARN("Couldn't create [{}] are you privileged ?", config.songs_dir);

    SongManager song_manager(config.songs_dir);
    song_manager.enumerate_songs();
    song_manager.set_current_song(0);
    song_manager.set_current_beatmap(0);
    if(song_manager.get_current_beatmap())
    {
        song_manager.get_current_beatmap()->loadAllSections();
    }

    SkinManager skin_manager(config.skins_dir);
    skin_manager.enumerate_skins();
    skin_manager.set_current_skin(0);

    graphics::handler::init(
        &song_manager, 
        &skin_manager,
        config.res_dir
    );
    audio::handler::init();

    Thread this_thread;
    this_thread.set_max_fps(1000);

    game_loop(song_manager, skin_manager, this_thread);

    clean();

    return true;
}

}
