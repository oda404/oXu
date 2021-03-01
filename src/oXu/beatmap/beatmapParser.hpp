#pragma once

#include<string>
#include<vector>
#include<memory>

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
    enum class Section
    {
        GENERAL    = 0,
        EDITOR     = 1,
        METADATA   = 2,
        DIFFICULTY = 3,
        EVENTS     = 4,
        TIMING     = 5,
        COLORS     = 6,
        OBJECTS    = 7,
        INVALID    = 255
    };

    enum class FieldStatus
    {
        /* field was parsed and set correctly */
        OK = 1,
        /* the field's name was invalid and not set */
        INVALID_NAME = 2,
        /* the field's value was invalid and not set */
        INVALID_VALUE = 3,
        /* the field was ignored. e.g. empty string */
        IGNORED = 4
    };

    template<typename T>
    struct FieldParseStatus
    {
        FieldParseStatus(T field_enum, FieldStatus status):
        field_enum(field_enum), status(status) {  }

        T field_enum;
        FieldStatus status;
    };

    Section get_section_enum_from_str(std::string str);

    FieldParseStatus<GeneralField> 
    parse_and_set_general_field(
        const std::string &field, 
        General &general
    );

    FieldParseStatus<EditorField> 
    parse_and_set_editor_field(
        const std::string &field, 
        Editor &editor
    );

    FieldParseStatus<MetadataField> 
    parse_and_set_metadata_field(
        const std::string &field, 
        Metadata &metadata
    );

    FieldParseStatus<DifficultyField> 
    parse_and_set_difficulty_field(
        const std::string &field, 
        Difficulty &diffictulty
    );

    void parse_and_set_event(
        const std::string &field, 
        Events &events
    );

    void parse_and_set_timing_point(
        const std::string &field, 
        std::vector<TimingPoint> &timingPoints
    );

    void parse_and_set_color(
        const std::string &field, 
        std::vector<Color> &colors
    );

    void parse_and_set_hit_object(
        const std::string &field, 
        std::vector<std::unique_ptr<HitObject>> &hitObjects, 
        const PlayField &playField, 
        const Difficulty &difficulty
    );
}
