// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"inputHandler.hpp"

int eventWatch(void *userdata, SDL_Event *event)
{
    /* Gets the exact mouse position + key timestamp when the key is pressed */
    if(event->type == SDL_KEYDOWN && ( event->key.keysym.sym == SDLK_x ))
    {
        static oxu::MapInfo &mapInfoI = oxu::MapInfo::getInstance();

        oxu::Vector2<int> mousePos;
        SDL_GetMouseState(&mousePos[0], &mousePos[1]);

        const SDL_Rect *lastACRect = mapInfoI.hitCircles[mapInfoI.hitObjCapBottom].getHCRect();

        if(mousePos[0] >= lastACRect->x &&
           mousePos[1] >= lastACRect->y &&
           mousePos[0] <= lastACRect->x + lastACRect->w &&
           mousePos[1] <= lastACRect->y + lastACRect->h)
           {
               mapInfoI.hitCircles[mapInfoI.hitObjCapBottom].hit();
           }

        return 0;
    }

    return 1;
}

oxu::InputHandler::InputHandler() { }

void oxu::InputHandler::init(SoundHandler *pSoundHandler)
{
    /* Add an event watch to check if a key is pressed */
    SDL_AddEventWatch(eventWatch, pSoundHandler);
}

void oxu::InputHandler::handleInput(bool &w_isClosed)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                w_isClosed = true;
                break;
        }
    }
}
