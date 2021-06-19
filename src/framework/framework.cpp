
#include<oxu/framework/framework.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/logger.hpp>
#include<SDL2/SDL.h>

namespace oxu::framework
{

bool init()
{
    logger::init();
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        OXU_LOG_ERR(SDL_GetError());
        status::set(status::FRAMEWORK_INIT_FAIL);
        return false;
    }

    return true;
}

void destroy()
{
    SDL_Quit();
}

}
