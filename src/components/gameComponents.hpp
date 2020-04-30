/*

    The GameComponents singleton struct contains any game
    components and/or game resources that need 
    to be accessed from different handlers
    and would be a pain to pass pointers of, plus the code
    would look messy

*/


#pragma once

#include<vector>

#include"game/hitCircle.hpp"
#include"cursor.hpp"
#include"../utils/timer.hpp"
#include"game/playField.hpp"

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

        /* Kinda used everywhere */
        Cursor cursor;

        /* Actual gameplay components */
        Timer gameTimer;

        PlayField playField;

        std::vector<HitCircle> hitCircles;
    };
}