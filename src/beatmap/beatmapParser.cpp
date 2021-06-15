
#include<sstream>
#include<unordered_map>
#include<oxu/beatmap/beatmapParser.hpp>
#include<oxu/core/window.hpp>
#include<oxu/beatmap/components/types.hpp>
#include<oxu/beatmap/components/hitCircle.hpp>
#include<oxu/beatmap/components/slider.hpp>
#include<oxu/core/logger.hpp>

#define UI unsigned int

namespace oxu
{
    static void strip_outer_whitespaces(std::string &str)
    {
        while(str[0] == ' ')
            str.erase(str.begin());
        
        while(str[str.size() - 1] == ' ')
            str.erase(str.end() - 1);
    }

    static void strip_control_chars(std::string &str)
    {
        for(UI i = 0; i < str.size(); ++i)
        {
            if(iscntrl(str[i]))
                str.erase(str.begin() + i--);
        }
    }

    static std::vector<std::string> 
    split_str(const std::string &line, const char &delimiter)
    {
        std::vector<std::string> out;
        std::string segment = "";

        for(const char &c: line)
        {
            if(c != delimiter)
            {
                segment += c;
                continue;
            }
            
            out.push_back(segment);
            segment = "";
        }

        out.push_back(segment);

        return out;
    }

    template<typename T>
    static bool cast_str_and_set(
        const std::string &str, 
        T &out
    )
    {
        std::stringstream ss(str);
        return static_cast<bool>(ss >> out);
    }

    static std::string get_field_value(const std::string &field)
    {
        std::string out = field.substr(field.find_first_of(':') + 1);
        strip_control_chars(out);
        strip_outer_whitespaces(out);
        return out;
    }

    static std::string get_field_name(const std::string &field)
    {
        std::string out = field.substr(0, field.find_first_of(':'));
        strip_control_chars(out);
        strip_outer_whitespaces(out);
        return out;
    }

    static void warn_invalid_field_name(
        const std::string &section,
        const std::string &field
    )
    {
        OXU_LOG_WARN("Ignoring invalid [{0}] field: '{1}'", section, field);
    }

    static void warn_invalid_field_value(
        const std::string &section,
        const std::string &field
    )
    {
        OXU_LOG_WARN("Ignoring [{0}] field: '{1}' because it's value is invalid", section, field);
    }

    Section get_section_enum_from_str(std::string str)
    {
        static const std::unordered_map<std::string, Section>
        sections_map = {
            { "[General]",      Section::GENERAL },
            { "[Editor]",       Section::EDITOR  },
            { "[Metadata]",     Section::METADATA },
            { "[Difficulty]",   Section::DIFFICULTY },
            { "[Events]",       Section::EVENTS },
            { "[TimingPoints]", Section::TIMING },
            { "[Colours]",      Section::COLORS },
            { "[HitObjects]",   Section::OBJECTS }
        };

        strip_control_chars(str);

        auto map_i = sections_map.find(str);

        if(map_i == sections_map.end())
            return Section::INVALID;

        return map_i->second;
    }

    FieldParseStatus<GeneralField> 
    parse_and_set_general_field(
        const std::string &field, 
        General &general_out
    )
    {
        static const std::unordered_map<std::string, GeneralField>
        general_fields_map = {
            { "AudioFilename",        GeneralField::AUDIO_FILENAME },
            { "AudioLeadIn",          GeneralField::AUDIO_LEAD_IN },
            { "PreviewTime",          GeneralField::PREVIEW_TIME },
            { "Countdown",            GeneralField::COUNTDOWN },
            { "SampleSet",            GeneralField::SAMPLE_SET },
            { "StackLeniency",        GeneralField::STACK_LENIENCY },
            { "Mode",                 GeneralField::MODE },
            { "LetterboxInBreaks",    GeneralField::LETTERBOX_IN_BREAKS },
            { "WidescreenStoryboard", GeneralField::WIDESCREEN_STORYBOARD }
        };

        std::string field_name = get_field_name(field);

        if(field_name.empty())
            return { GeneralField::INVALID, FieldStatus::IGNORED };

        const auto map_i = general_fields_map.find(field_name);
        if(map_i == general_fields_map.end())
        {
            warn_invalid_field_name("General", field);
            return { GeneralField::INVALID, FieldStatus::INVALID_NAME };
        }

        const GeneralField field_name_enum = map_i->second;
        const std::string field_value = get_field_value(field);

        if(field_value.empty())
            return { field_name_enum, FieldStatus::INVALID_VALUE };

        bool is_valid = true;

        /* no longer hurts my brain :) */
        switch(field_name_enum)
        {
        case GeneralField::AUDIO_FILENAME:
            general_out.audioFilename = field_value;
            break;

        case GeneralField::AUDIO_LEAD_IN:
            is_valid = cast_str_and_set<int>(field_value, general_out.audioLeadIn);
            break;

        case GeneralField::PREVIEW_TIME:
            is_valid = cast_str_and_set<int>(field_value, general_out.previewTime);
            break;

        case GeneralField::COUNTDOWN:
            is_valid = cast_str_and_set<int>(field_value, general_out.countdown);
            break;

        case GeneralField::SAMPLE_SET:
            general_out.sampleSet = field_value;
            break;

        case GeneralField::STACK_LENIENCY:
            is_valid = cast_str_and_set<float>(field_value, general_out.stackLeniency);
            break;

        case GeneralField::MODE:
            is_valid = cast_str_and_set<std::uint8_t>(field_value, general_out.mode);
            break;

        case GeneralField::LETTERBOX_IN_BREAKS:
            is_valid = cast_str_and_set<int>(field_value, general_out.letterboxInBreaks);
            break;

        case GeneralField::WIDESCREEN_STORYBOARD:
            is_valid = cast_str_and_set<int>(field_value, general_out.widescreenStoryboard);
            break;

        default:
            /* shouldn't happen, is here to suppress warnings */
            break;
        }

        if(is_valid)
        {
            return { field_name_enum, FieldStatus::OK };
        }
        else
        {
            warn_invalid_field_value("General", field);
            return { field_name_enum, FieldStatus::INVALID_VALUE };   
        }
    }

    FieldParseStatus<MetadataField> 
    parse_and_set_metadata_field(
        const std::string &field, 
        Metadata &metadata_out
    )
    {
        static const std::unordered_map<std::string, MetadataField>
        metadata_fields_map = {
            { "Title",         MetadataField::TITLE },
            { "TitleUnicode",  MetadataField::TITLE_UNICODE },
            { "Artist",        MetadataField::ARTIST },
            { "ArtistUnicode", MetadataField::ARTIST_UNICODE },
            { "Creator",       MetadataField::CREATOR },
            { "Version",       MetadataField::VERSION },
            { "Source",        MetadataField::SOURCE },
            { "Tags",          MetadataField::TAGS },
            { "BeatmapID",     MetadataField::BEATMAP_ID },
            { "BeatmapSetID",  MetadataField::BEATMAP_SET_ID }
        };

        std::string field_name = get_field_name(field);

        if(field_name.empty())
            return { MetadataField::INVALID, FieldStatus::IGNORED };

        const auto map_i = metadata_fields_map.find(field_name);

        if(map_i == metadata_fields_map.end())
        {
            warn_invalid_field_name("Metadata", field);
            return { MetadataField::INVALID, FieldStatus::INVALID_NAME };
        }

        const MetadataField field_name_enum = map_i->second;
        const std::string field_value = get_field_value(field);

        if(field_value.empty())
            return { field_name_enum, FieldStatus::INVALID_VALUE };

        bool is_valid = true;

        switch(field_name_enum)
        {
        case MetadataField::TITLE:
            metadata_out.title = field_value;
            break;

        case MetadataField::TITLE_UNICODE:
            metadata_out.titleUnicode = field_value;
            break;

        case MetadataField::ARTIST:
            metadata_out.artist = field_value;
            break;

        case MetadataField::ARTIST_UNICODE:
            metadata_out.artistUnicode = field_value;
            break;

        case MetadataField::CREATOR:
            metadata_out.creator = field_value;
            break;

        case MetadataField::VERSION:
            metadata_out.version = field_value;
            break;

        case MetadataField::SOURCE:
            metadata_out.source = field_value;
            break;

        case MetadataField::TAGS:
            metadata_out.tags = split_str(field_value, ' ');
            break;

        case MetadataField::BEATMAP_ID:
            is_valid = cast_str_and_set<int>(field_value, metadata_out.beatmapID);
            break;

        case MetadataField::BEATMAP_SET_ID:
            is_valid =  cast_str_and_set<int>(field_value, metadata_out.beatmapSetID);
            break;

        default:
            /* shouldn't happen, is here to suppress warnings */
            break;
        }

        if(is_valid)
        {
            return { field_name_enum, FieldStatus::OK };
        }
        else
        {
            warn_invalid_field_value("Metadata", field);
            return { field_name_enum, FieldStatus::INVALID_VALUE };   
        }
    }

    FieldParseStatus<EditorField> 
    parse_and_set_editor_field(
        const std::string &field, 
        Editor &editor_out
    )
    {
        static const std::unordered_map<std::string, EditorField>
        editor_fields_map = {
            { "Bookmarks",       EditorField::BOOKMARKS },
            { "DistanceSpacing", EditorField::DISTANCE_SPACING },
            { "BeatDivisor",     EditorField::BEAT_DIVISOR },
            { "GridSize",        EditorField::GRID_SIZE },
            { "TimelineZoom",    EditorField::TIMELINE_ZOOM }
        };

        std::string field_name = get_field_name(field);

        if(field_name.empty())
            return { EditorField::INVALID, FieldStatus::IGNORED };

        const auto map_i = editor_fields_map.find(field_name);

        if(map_i == editor_fields_map.end())
        {
            warn_invalid_field_name("Editor", field);
            return { EditorField::INVALID, FieldStatus::INVALID_NAME };
        }

        const EditorField field_name_enum = map_i->second;
        const std::string field_value = get_field_value(field);

        if(field_value.empty())
            return { field_name_enum, FieldStatus::INVALID_VALUE };

        bool is_valid = true;

        switch(field_name_enum)
        {
        case EditorField::BOOKMARKS:
            {
                const std::vector<std::string> bookmarks_str = 
                split_str(field_value, ',');
                editor_out.bookmarks.resize(bookmarks_str.size());
                
                for(UI i = 0; i < bookmarks_str.size(); ++i)
                {
                    is_valid = cast_str_and_set<int>(
                        bookmarks_str[i],
                        editor_out.bookmarks[i]
                    );
                    
                    if(!is_valid) break;
                }
            }
            break;

        case EditorField::DISTANCE_SPACING:
            is_valid = cast_str_and_set<float>(field_value, editor_out.distanceSpacing);
            break;

        case EditorField::BEAT_DIVISOR:
            is_valid = cast_str_and_set<float>(field_value, editor_out.beatDivisor);
            break;

        case EditorField::GRID_SIZE:
            is_valid = cast_str_and_set<int>(field_value, editor_out.gridSize);
            break;

        case EditorField::TIMELINE_ZOOM:
            is_valid = cast_str_and_set<float>(field_value, editor_out.timelineZoom);
            break;

        default:
            /* shouldn't happen, is here to suppress warnings */
            break;
        }

        if(is_valid)
        {
            return { field_name_enum, FieldStatus::OK };
        }
        else
        {
            warn_invalid_field_value("Editor", field);
            return { field_name_enum, FieldStatus::INVALID_VALUE };   
        }
    }

    FieldParseStatus<DifficultyField> 
    parse_and_set_difficulty_field(
        const std::string &field, 
        Difficulty &difficulty_out
    )
    {
        static const std::unordered_map<std::string, DifficultyField>
        difficulty_fields_map = {
            { "HPDrainRate",       DifficultyField::HP_DRAIN_RATE },
            { "CircleSize",        DifficultyField::CIRCLE_SIZE },
            { "OverallDifficulty", DifficultyField::OVERALL_DIFFICULTY },
            { "ApproachRate",      DifficultyField::APPROACH_RATE },
            { "SliderMultiplier",  DifficultyField::SLIDER_MULTIPLIER },
            { "SliderTickRate",    DifficultyField::SLIDER_TICK_RATE }
        };

        std::string field_name = get_field_name(field);

        if(field_name.empty())
            return { DifficultyField::INVALID, FieldStatus::IGNORED };

        const auto map_i = difficulty_fields_map.find(field_name);

        if(map_i == difficulty_fields_map.end())
        {
            warn_invalid_field_name("Difficulty", field);
            return { DifficultyField::INVALID, FieldStatus::INVALID_NAME };
        }

        const DifficultyField field_name_enum = map_i->second;
        const std::string field_value = get_field_value(field);

        if(field_value.empty())
            return { field_name_enum, FieldStatus::INVALID_VALUE };

        bool is_valid = true;

        switch(field_name_enum)
        {
        case DifficultyField::HP_DRAIN_RATE:
            is_valid = cast_str_and_set<float>(field_value, difficulty_out.HPDrainRate);
            break;

        case DifficultyField::CIRCLE_SIZE:
            is_valid = cast_str_and_set<float>(field_value, difficulty_out.circleSize);
            break;

        case DifficultyField::OVERALL_DIFFICULTY:
            is_valid = cast_str_and_set<float>(field_value, difficulty_out.overallDifficulty);
            break;

        case DifficultyField::APPROACH_RATE:
            is_valid = cast_str_and_set<float>(field_value, difficulty_out.approachRate);
            break;

        case DifficultyField::SLIDER_MULTIPLIER:
            is_valid = cast_str_and_set<float>(field_value, difficulty_out.sliderMultiplier);
            break;

        case DifficultyField::SLIDER_TICK_RATE:
            is_valid = cast_str_and_set<float>(field_value, difficulty_out.sliderTickRate);
            break;

        default:
            /* shouldn't happen, is here to suppress warnings */
            break;
        }

        if(is_valid)
        {
            return { field_name_enum, FieldStatus::OK };
        }
        else
        {
            warn_invalid_field_value("Difficulty", field);
            return { field_name_enum, FieldStatus::INVALID_VALUE };   
        }
    }

    static ObjectType parse_hit_obj_type(std::uint8_t &type)
    {
        if(type & (1 << 0))
        {
            return ObjectType::CIRCLE;
        }
        else if(type & (1 << 1))
        {
            return ObjectType::SLIDER;
        }
        else if(type & (1 << 3))
        {
            return ObjectType::SPINNER;
        }

        return ObjectType::UNKNOWN;
    }

    static bool parse_and_set_control_points(
        const std::string &line, 
        std::vector<Vector2<float>> &controlPoints
    )
    {
        std::string x_buff = "", y_buff = "";
        float x, y;
        bool read_x = true;
        
        if(line[1] != '|')
        {
            return false;
        }

        for(size_t i = 2; i < line.size(); ++i)
        {
            if(line[i] == ':')
            {
                read_x = false;
                continue;
            }
            else if(line[i] == '|')
            {
                read_x = true;

                if(
                    !cast_str_and_set<float>(x_buff, x) || 
                    !cast_str_and_set<float>(y_buff, y)
                )
                {
                    return false;
                }

                controlPoints.emplace_back(x, y);

                x_buff = "";
                y_buff = "";
                continue;
            }


            if(read_x)
                x_buff += line[i];
            else
                y_buff += line[i];
        }

        if(
            !cast_str_and_set<float>(x_buff, x) || 
            !cast_str_and_set<float>(y_buff, y)
        )
        {
            return false;
        }

        controlPoints.emplace_back(x, y);

        return true;
    }

    static void warn_invalid_object(const std::string &obj)
    {
        OXU_LOG_WARN("Ignoring invalid hit object \'{0}\'", obj);
    }

#define OBJ_X         0
#define OBJ_Y         1
#define OBJ_TIME      2
#define OBJ_TYPE      3
#define OBJ_HIT_SOUND 4
#define OBJ_PARAMS    5
#define SLD_REPEATS   6
#define SLD_LENGTH    7

#define MIN_EXPECTED_CIRCLE_TOKS 6
#define MIN_EXPECTED_SLD_TOKS 7

    void parse_and_set_hit_object(
        const std::string &line, 
        std::vector<std::unique_ptr<HitObject>> &hit_objects_p, 
        const PlayField &playField, 
        const Difficulty &difficulty
    )
    {
        const std::vector<std::string> obj_tokens = split_str(line, ',');
        if(obj_tokens.size() < MIN_EXPECTED_CIRCLE_TOKS)
        {
            warn_invalid_object(line);
            return;
        }

        ObjectInfo obj_info;

        if(
            !cast_str_and_set<float>(obj_tokens[OBJ_X], obj_info.position.x)      || 
            !cast_str_and_set<float>(obj_tokens[OBJ_Y], obj_info.position.y)      ||
            !cast_str_and_set<std::uint32_t>(obj_tokens[OBJ_TIME], obj_info.time) ||
            !cast_str_and_set<std::uint8_t>(obj_tokens[OBJ_TYPE], obj_info.type)
        )
        {
            warn_invalid_object(line);
            return;
        }

        /* scale the position */
        obj_info.position = 
        playField.getStartPoint() + obj_info.position * window::get_oxu_px();

        const ObjectType parsed_obj_type = parse_hit_obj_type(obj_info.type);

        switch(parsed_obj_type)
        {
        case ObjectType::CIRCLE:
            hit_objects_p.emplace_back(std::make_unique<HitCircle>(
                obj_info,
                difficulty
            ));
            break;

        case ObjectType::SLIDER:
            {
                if(obj_tokens.size() < MIN_EXPECTED_SLD_TOKS)
                {
                    warn_invalid_object(line);
                    return;
                }

                SliderInfo slider_info;

                /* set curve type */
                if(obj_tokens[OBJ_PARAMS].length() < 5) /* min can be ?|X:Y */
                {
                    warn_invalid_object(line);
                    return;
                }

                switch(obj_tokens[OBJ_PARAMS][0])
                {
                case 'P': /* perfect circle */ 
                    slider_info.curve_type = SliderCurveType::CIRCLE;
                    break;
                case 'B': /* bezier */
                    slider_info.curve_type = SliderCurveType::BEZIER;
                    break;
                case 'L': /* linear */
                    slider_info.curve_type = SliderCurveType::LINEAR;
                    break;
                default:
                    warn_invalid_object(line);
                    return;
                }

                if(
                    !parse_and_set_control_points(obj_tokens[OBJ_PARAMS], slider_info.curve_points) ||
                    !cast_str_and_set<std::uint16_t>(obj_tokens[SLD_REPEATS], slider_info.slides)   ||
                    !cast_str_and_set<double>(obj_tokens[SLD_LENGTH], slider_info.length)
                )
                {
                    warn_invalid_object(line);
                    return;
                }

                hit_objects_p.emplace_back(std::make_unique<Slider>(
                    obj_info,
                    slider_info,
                    difficulty
                ));
            }
            break;

        case ObjectType::SPINNER:
            break;

        default:
            warn_invalid_object(line);
            break;
        }
    }
}
