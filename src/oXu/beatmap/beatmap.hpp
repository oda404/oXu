#pragma once

#include<string>
#include<vector>
#include<fstream>
#include<cstdint>
#include<map>

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

#include<oXu/core/threading/threads.hpp>

namespace oxu
{
    class Beatmap
    {
    private:
        uint8_t fileFormat;

        std::vector<TimingPoint> timingPoints;

    public:
        Beatmap(const std::string &path_p);

        std::string path;
        
        General general;
        Editor editor;
        Metadata metadata;
        Difficulty difficulty;
        Events events;

        std::vector<HitObject> hitObjects;

        uint32_t objTopCap = 0;
        uint32_t objBotCap = 0;

        uint16_t startPaddingTime = 0;

        Timer timer;

        void loadGenericInfo();
        void loadGameInfo();

        void updateObjects(const double &delta);

        void start();
    };
}
