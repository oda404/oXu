// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"inputHandler.hpp"

int eventWatch(void *userdata, SDL_Event *event)
{
    /* Gets the exact mouse position + key timestamp when the key is pressed */
    if(event->type == SDL_KEYDOWN && ( event->key.keysym.sym == SDLK_x ))
    {
        oxu::BeatmapManager *mapManager = (oxu::BeatmapManager*)userdata;

        oxu::Vector2<int> mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        const SDL_Rect *lastACRect = mapManager->getObjectsInfo().getHCAt(mapManager->getObjectsInfo().HCBotCap).getHCRect();

        if(mousePos.x >= lastACRect->x &&
           mousePos.y >= lastACRect->y &&
           mousePos.x <= lastACRect->x + lastACRect->w &&
           mousePos.y <= lastACRect->y + lastACRect->h)
           {
               mapManager->getObjectsInfo().getHCAt(mapManager->getObjectsInfo().HCBotCap).hit();
           }

        return 0;
    }

    return 1;
}

void oxu::InputHandler::init(BeatmapManager *mapManager)
{
    this->beatmapManager = mapManager;
    /* Add an event watch to check if a key is pressed */
    SDL_AddEventWatch(eventWatch, mapManager);
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

void oxu::InputHandler::handleEvents()
{

}
