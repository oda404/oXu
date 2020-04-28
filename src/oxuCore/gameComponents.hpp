/*

    The GameComponents singleton struct contains any game
    components and/or game resources that need 
    to be accessed from different handlers
    and would be a pain to pass pointers of, plus the code
    would look messy

*/


#pragma once

#include<vector>

#include"../oxuGameComponents/hitCircle.hpp"
#include "../oxuGameComponents/cursor.hpp"

namespace oxu
{
    struct GameComponents
    {
    private:
        /* Make default constructor private */
        GameComponents();

    public:
        static GameComponents &getInstance();

        /* Disable copy-ctor */
        GameComponents(GameComponents const&) = delete;

        /* Disable move-ctor */
        GameComponents(GameComponents&&) = delete;

        /* Game components */
        Cursor cursor;

        std::vector<HitCircle> hitCircles;
    };
}