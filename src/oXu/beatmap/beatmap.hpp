#pragma once

#include<string>
#include<vector>
#include<cstdint>

#include<oXu/beatmap/sections/general.hpp>
#include<oXu/beatmap/sections/editor.hpp>
#include<oXu/beatmap/sections/metadata.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>

#include<oXu/beatmap/components/hitObject.hpp>

#include<oXu/utils/timer.hpp>

namespace oxu
{
    class Beatmap
    {
    private:
        uint8_t fileFormat;

    public:
        Beatmap(const std::string &path_p);

        std::string path;
        
        General general;
        Editor editor;
        Metadata metadata;
        Difficulty difficulty;

        std::vector<HitObject> hitObjects;

        uint32_t objTopCap = 0;
        uint32_t objBotCap = 0;

        Timer timer;

        void loadGenericInfo();
        void loadGameInfo();
        void updateObjects(const double &delta);
        void start();
    };
}
