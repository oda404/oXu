#include<SDL2/SDL.h>
#include<oXu/core/logger.hpp>
#include<oXu/core/fs.hpp>
#include<oXu/core/status.hpp>
#include<oXu/core/window.hpp>
#include<oXu/graphics/handler.hpp>
#include<oXu/audio/handler.hpp>
#include<oXu/beatmap/songManager.hpp>
#include<oXu/core/threading/thread.hpp>

namespace oxu
{
    static Thread c_this_thread;
    static SDL_Window *cp_game_window = nullptr;
    static SongManager *cp_song_manager = nullptr;
    static SkinManager *cp_skin_manager = nullptr;

    bool init()
    {
        logger::init();
        fs::set_songs_dir();
        fs::set_skins_dir();

        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            OXU_LOG_ERR(SDL_GetError());
            Status::code = Status::SDL_INIT_FAIL;
            return false;
        }

        cp_game_window = SDL_CreateWindow(
            "oXu!",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            0,
            0,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );

        if(!cp_game_window)
        {
            OXU_LOG_ERR(SDL_GetError());
            Status::code = Status::WINDOW_CREATE_FAIL;
		    return false;
        }

        window::set_window_size(cp_game_window, { 800, 600 });

        cp_song_manager = new SongManager();
        cp_skin_manager = new SkinManager();

        cp_song_manager->enumerateSongs();
        cp_song_manager->setCurrentSong(0);
		cp_song_manager->setCurrentBeatmap(0);
		if(cp_song_manager->getCurrentBeatmap())
		{
			cp_song_manager->getCurrentBeatmap()->loadGenericInfo();
			cp_song_manager->getCurrentBeatmap()->loadGameInfo();
		}

        GraphicsHandler::init(cp_game_window, cp_song_manager, cp_skin_manager);
        AudioHandler::init();

        return true;
    }
    
    void start()
    {
        SDL_Event sdl_event;
        bool window_open = true;
        Beatmap *p_current_beatmap = cp_song_manager->getCurrentBeatmap();

        while(window_open)
        {
            c_this_thread.limitFPS();

            if(p_current_beatmap)
            {
                p_current_beatmap->updateObjects(c_this_thread.getDelta());
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

    void clean()
    {
        GraphicsHandler::shutDown();
        AudioHandler::shutDown();
        SDL_DestroyWindow(cp_game_window);
        cp_game_window = nullptr;
        SDL_Quit();
    }
}
