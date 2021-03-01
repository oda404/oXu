#include"game.hpp"
#include<SDL2/SDL.h>
#include<oXu/core/logger.hpp>
#include<oXu/core/fs.hpp>
#include<oXu/core/status.hpp>
#include<oXu/core/window.hpp>
#include<oXu/graphics/handler.hpp>
#include<oXu/audio/handler.hpp>
#include<oXu/skin/skinManager.hpp>
#include<oXu/beatmap/songManager.hpp>
#include<oXu/core/threading/thread.hpp>

namespace oxu
{
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

        while(window_open)
        {
            this_thread_p.limitFPS();

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

    static void clean(
        SDL_Window *p_game_window_p
    )
    {
        graphics::handler::shut_down();
        AudioHandler::shutDown();
        SDL_DestroyWindow(p_game_window_p);
        p_game_window_p = nullptr;
        SDL_Quit();
    }

    bool init(const Config &config)
    {
        logger::init();

        if(!fs::is_config_dir_valid(config.configDirPath))
        {
            fs::validate_config_dir(config.configDirPath);
        }

        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            OXU_LOG_ERR(SDL_GetError());
            status::set(status::SDL_INIT_FAIL);
            return false;
        }

        window::Window window;

        SDL_Window *p_game_window = nullptr;

        p_game_window = SDL_CreateWindow(
            "oXu!",
            0, 0, 0, 0,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );

        if(!p_game_window)
        {
            OXU_LOG_ERR(SDL_GetError());
            status::set(status::WINDOW_CREATE_FAIL);
		    return false;
        }

        window::set_window_size(p_game_window, config.screenSize);

        SongManager song_manager(window, config.configDirPath);
        song_manager.enumerateSongs();
        song_manager.setCurrentSong(0);
		song_manager.setCurrentBeatmap(0);
		if(song_manager.getCurrentBeatmap())
		{
			song_manager.getCurrentBeatmap()->loadAllSections();
		}

        SkinManager skin_manager(config.configDirPath);
        skin_manager.enumerateSkins();
        skin_manager.setCurrentSkin(0);

        Thread this_thread;
        this_thread.setMaxFPS(1000);

        graphics::handler::init(
            p_game_window, 
            &song_manager, 
            &skin_manager,
            config.configDirPath
        );
        AudioHandler::init();

        game_loop(song_manager, skin_manager, this_thread);

        clean(p_game_window);

        return true;
    }
}
