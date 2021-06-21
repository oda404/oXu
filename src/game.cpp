
#include<SDL2/SDL.h>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/window.hpp>
#include<oxu/framework/graphics/handler.hpp>
#include<oxu/framework/audio/handler.hpp>
#include<oxu/framework/threading/thread.hpp>
#include<oxu/framework/framework.hpp>
#include<oxu/game.hpp>
#include<oxu/skin/skinManager.hpp>
#include<oxu/beatmap/songManager.hpp>

namespace oxu
{

using namespace framework;
using namespace framework::threading;
namespace stdfs = std::filesystem;

static void game_loop(
    SongManager &song_manager_p,
    SkinManager &skin_manager_p,
    Thread &this_thread_p
)
{
    SDL_Event sdl_event;
    bool window_open = true;
    Beatmap *p_current_beatmap = song_manager_p.getCurrentBeatmap();
    if(p_current_beatmap)
    {
        p_current_beatmap->start();
    }

    this_thread_p.start();
    while(window_open)
    {
        this_thread_p.capFPS();

        if(p_current_beatmap)
        {
            p_current_beatmap->updateObjects(this_thread_p.getDelta());
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

    uint32_t flags = (
        window::InitFlags::OPENGL |
        window::InitFlags::SHOWN
    );

    if(!window::init("oxu", config.window_size, flags))
    {
        return false;
    }

    SongManager song_manager(config.songs_dir);
    song_manager.enumerateSongs();
    song_manager.setCurrentSong(0);
    song_manager.setCurrentBeatmap(0);
    if(song_manager.getCurrentBeatmap())
    {
        song_manager.getCurrentBeatmap()->loadAllSections();
    }

    SkinManager skin_manager(config.skins_dir);
    skin_manager.enumerateSkins();
    skin_manager.setCurrentSkin(0);

    SDL_Window *p_game_window = window::get_native_window();

    graphics::handler::init(
        p_game_window, 
        &song_manager, 
        &skin_manager,
        config.res_dir
    );
    audio::handler::init();

    Thread this_thread;
    this_thread.setMaxFPS(1000);

    game_loop(song_manager, skin_manager, this_thread);

    clean();

    return true;
}

}
