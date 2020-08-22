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

namespace oxu
{
    void parseAndSetGeneral(const std::string &line, General &general);

    void parseAndSetEditor(const std::string &line, Editor &editor);

    void parseAndSetMetadata(const std::string &line, Metadata &metadata);

    void parseAndSetDifficulty(const std::string &line, Difficulty &diffictulty);

    void parseAndSetEvents(const std::string &line, Events &events);

    void parseAndAddTimingPoint(const std::string &line, std::vector<TimingPoint> &timingPoints);

    void parseAndSetColors(const std::string &line, std::vector<Color> &colors);

    void parseAndAddHitObject(const std::string &line, std::vector<HitObject> &hitObjects, const PlayField &playField, const Difficulty &difficulty);
}
