#pragma once

#include<string>
#include<vector>

#include<oXu/beatmap/sections/general.hpp>
#include<oXu/beatmap/sections/editor.hpp>
#include<oXu/beatmap/sections/metadata.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/beatmap/sections/events.hpp>
#include<oXu/beatmap/sections/timingPoint.hpp>
#include<oXu/beatmap/sections/color.hpp>
#include<oXu/beatmap/components/hitObject.hpp>
#include<oXu/beatmap/components/playField.hpp>

#include<oXu/utils/logger.hpp>

namespace oxu
{
    void parseGeneral(const std::string &line, General &general);

    void parseEditor(const std::string &line, Editor &editor);

    void parseMetadata(const std::string &line, Metadata &metadata);

    void parseDifficulty(const std::string &line, Difficulty &diffictulty);

    void parseEvents(const std::string &line, Events &events);

    void parseTimingPoints(const std::string &line, std::vector<TimingPoint> &timingPoints);

    void parseColors(const std::string &line, std::vector<Color> &colors);

    void parseObjects(const std::string &line, std::vector<HitObject> &hitObjects, const PlayField &playField, const Difficulty &difficulty);
}
