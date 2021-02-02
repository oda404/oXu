// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"handler.hpp"

#include<oXu/core/status.hpp>
#include<oXu/core/logger.hpp>
#include<oXu/graphics/renderer.hpp>
#include<oXu/core/threading/thread.hpp>

namespace oxu::graphics::handler
{
    static Thread c_this_thread;
    static SDL_Window *cp_game_window = nullptr;
    static SongManager *cp_song_manager;
    static SkinManager *cp_skin_manager;

    static void start_thread()
    {
        Request request;
        Beatmap *p_current_beatmap = cp_song_manager->getCurrentBeatmap();

        while(true)
        {
            c_this_thread.limitFPS();
            
            while(c_this_thread.pipeline.pollRequest(request))
            {
                switch(request.instruction)
                {
                case Graphics::HALT_THREAD:
                    return;
                }
            }

            Renderer::clear();

            if(p_current_beatmap)
            {
                p_current_beatmap->renderObjects(*cp_skin_manager->getCurrentSkin());
            }

            Renderer::render();
        }
    }

    static void init_thread()
    {
        /* Initiate the renderer here because it needs the new thread context */
        if(!Renderer::init(cp_game_window, Renderer::Backends::OPENGL))
        {
            c_this_thread.doneInit = true;
            return;
        }

        if(cp_skin_manager->getCurrentSkin())
        {
            cp_skin_manager->getCurrentSkin()->setCursor();
            cp_skin_manager->getCurrentSkin()->loadTextures();
        }

        c_this_thread.doneInit = true;
        start_thread();
    }

    void init(SDL_Window *window_p, SongManager *songManager_p, SkinManager *skinManager_p)
    {
        cp_song_manager = songManager_p;
        cp_skin_manager = skinManager_p;
        cp_game_window = window_p;

        c_this_thread.setMaxFPS(240);
        /* paranoia */
        c_this_thread.doneInit = false;
        c_this_thread.start([] { init_thread(); });
        /* wait for the thread to initiate */
        while(!c_this_thread.doneInit);
    }

    void shut_down()
    {
        c_this_thread.pipeline.makeRequest(Graphics::HALT_THREAD);
        c_this_thread.join();
        Renderer::destroy();
    }
}
