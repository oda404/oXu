
#include<SDL2/SDL.h>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/window.hpp>
#include<oxu/framework/threading/thread.hpp>
#include<oxu/framework/framework.hpp>
#include<oxu/framework/graphics/renderer.hpp>
#include<oxu/framework/fs.hpp>
#include<oxu/game.hpp>
#include<oxu/skin/skinManager.hpp>
#include<oxu/beatmap/songManager.hpp>

namespace oxu
{

using namespace framework::threading;
using namespace framework::graphics;
namespace window = framework::window;
namespace oxufs = oxu::framework::fs;
namespace stdfs = std::filesystem;

static void clean()
{
    renderer::destroy();
    window::destroy();
    framework::destroy();
}

bool init(const GameConfig &config)
{
    if(!oxufs::dir_create(config.res_dir))
        OXU_LOG_WARN("Couldn't create [{}] are you privileged ?", config.res_dir);
    if(!oxufs::dir_create(config.skins_dir))
        OXU_LOG_WARN("Couldn't create [{}] are you privileged ?", config.skins_dir);
    if(!oxufs::dir_create(config.songs_dir))
        OXU_LOG_WARN("Couldn't create [{}] are you privileged ?", config.songs_dir);

    if(!framework::init())
        return false;

    if(!window::init("oxu", config.window_size))
        return false;

    if(!renderer::init(renderer::BackendType::OPENGL, config.res_dir))
        return false;

    SongManager song_manager(config.songs_dir);
    song_manager.enumerate_songs();
    song_manager.set_current_song(0);
    song_manager.set_current_beatmap(0);

    SkinManager skin_manager(config.skins_dir);
    skin_manager.enumerate_skins();
    skin_manager.set_current_skin(0);
    
    Beatmap *beatmap = song_manager.get_current_beatmap();
    Skin *skin = skin_manager.get_current_skin();

    if(!beatmap)
    {
        OXU_LOG_ERROR("Panic: Going nowhere without my beatmap! :(");
        clean();
        return false;
    }

    if(!skin)
    {
        OXU_LOG_ERROR("Panic: Going nowhere without my skin! :(");
        clean();
        return false;
    }
    
    beatmap->loadAllSections();
    skin->loadTextures();
    skin->setCursor();

    Thread this_thread;
    bool running = true;

    this_thread.set_max_fps(1000);
    this_thread.start();

    beatmap->start();

    while(running)
    {
        static SDL_Event sdlevent;

        this_thread.cap_fps();

        renderer::clear();

        beatmap->updateObjects(this_thread.get_delta());
        beatmap->renderObjects(*skin);

        renderer::render();

        while(SDL_PollEvent(&sdlevent))
        {
            switch(sdlevent.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }
    }

    clean();

    return true;
}

}
