#pragma once

#include<string>
#include<vector>
#include<fstream>
#include<cstdint>

#include<oXu/beatmap/sections/general.hpp>
#include<oXu/beatmap/sections/editor.hpp>
#include<oXu/beatmap/sections/metadata.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/beatmap/sections/events.hpp>
#include<oXu/beatmap/sections/timingPoint.hpp>
#include<oXu/beatmap/sections/color.hpp>
#include<oXu/beatmap/sections/config.hpp>

#include<oXu/beatmap/components/playField.hpp>
#include<oXu/beatmap/components/hitObject.hpp>

#include<oXu/beatmap/beatmapParser.hpp>

#include<oXu/utils/timer.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    class Beatmap
    {
    private:
        std::string path;

    public:
        Beatmap(const std::string &path_p);
        
        uint8_t fileFormat;
        General general;
        Editor editor;
        Metadata metadata;
        Difficulty difficulty;
        Events events;
        std::vector<TimingPoint> timingPoints;
        std::vector<HitObject> hitObjects;

        Timer timer;
        int32_t objTopCap = -1;
        int32_t objBotCap = 0;

        void loadGenericInfo();
        void loadGameInfo();
    };
}
