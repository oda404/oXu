#include"beatmapParser.hpp"

#include<sstream>

#include<oXu/core/window.hpp>
#include<oXu/beatmap/components/types.hpp>
#include<oXu/beatmap/components/hitCircle.hpp>
#include<oXu/beatmap/components/slider.hpp>
#include<oXu/core/logger.hpp>

namespace oxu
{
    static void sanitizeStr(std::string &str)
    {
        if(str[0] == ' ')
        {
            str.erase(str.begin());
        }

        for(size_t i = 0; i < str.size(); ++i)
        {
            if(strchr("\r\n", str[i]))
            {
                str.erase(str.begin() + i);
            }
        }
    }

    static std::vector<std::string> getSplitStr(const std::string &line, const char &ch)
    {
        std::vector<std::string> result;
        std::string segment = "";

        for(const char &c: line)
        {
            if(c != ch)
            {
                segment += c;
                continue;
            }
            
            result.push_back(segment);
            segment = "";
        }

        result.push_back(segment);

        return result;
    }

    template<typename T>
    static bool setAttr(const std::string &line, T &destAttr)
    {
        std::stringstream ss(line);

        if(!(ss >> destAttr))
        {
            destAttr = 0;
            return false;
        }

        return true;
    }

    static std::string stripAttr(const std::string &line)
    {
        std::string result = line.substr(line.find_first_of(':') + 1, line.size());

        sanitizeStr(result);

        return result;
    }

    static std::string getAttrName(const std::string &line)
    {
        return line.substr(0, line.find_first_of(':'));
    }

    void parseAndSetGeneral(const std::string &line, General &general)
    {
        std::string attrName = getAttrName(line);
        std::string strippedAttr = stripAttr(line);

        /* This shit hurts my brain and it's probably pretty bad but I can't think of another way of doing it */
        if(attrName == "AudioFilename")
        {
            general.audioFilename = stripAttr(line);
        }
        else if(attrName == "AudioLeadIn")
        {
            setAttr<int>(strippedAttr, general.audioLeadIn);
        }
        else if(attrName == "PreviewTime")
        {
            setAttr<int>(strippedAttr, general.previewTime);
        }
        else if(attrName == "Countdown")
        {
            setAttr<int>(strippedAttr, general.countdown);
        }
        else if(attrName == "SampleSet")
        {
            general.sampleSet = stripAttr(line);
        }
        else if(attrName == "StackLeniency")
        {
            setAttr<float>(strippedAttr, general.stackLeniency);
        }
        else if(attrName == "Mode")
        {
            setAttr<uint8_t>(strippedAttr, general.mode);
        }
        else if(attrName == "LetterboxInBreaks")
        {
            setAttr<int>(strippedAttr, general.letterboxInBreaks);
        }
        else if(attrName == "WidescreenStoryboard")
        {
            setAttr<int>(strippedAttr, general.widescreenStoryboard);
        }
    }

    void parseAndSetMetadata(const std::string &line, Metadata &metadata)
    {
        std::string attrName = getAttrName(line);
        std::string strippedAttr = stripAttr(line);

        if(attrName == "Title")
        {
            metadata.title = stripAttr(line);
        }
        else if(attrName == "TitleUnicode")
        {
            metadata.titleUnicode = stripAttr(line);
        }
        else if(attrName == "Artist")
        {
            metadata.artist = stripAttr(line);
        }
        else if(attrName == "ArtistUnicode")
        {
            metadata.artistUnicode = stripAttr(line);
        }
        else if(attrName == "Creator")
        {
            metadata.creator = stripAttr(line);
        }
        else if(attrName == "Version")
        {
            metadata.version = stripAttr(line);
        }
        else if(attrName == "Source")
        {
            metadata.source = stripAttr(line);
        }
        else if(attrName == "Tags")
        {
            //TODO
        }
        else if(attrName == "BeatmapID")
        {
            setAttr<int>(strippedAttr, metadata.beatmapID);
        }
        else if(attrName == "BeatmapSetID")
        {
            setAttr<int>(strippedAttr, metadata.beatmapSetID);
        }
    }

    void parseAndSetDifficulty(const std::string &line, Difficulty &difficulty)
    {
        std::string attrName = getAttrName(line);
        std::string strippedAttr = stripAttr(line);

        if(attrName == "HPDrainRate")
        {
            setAttr<float>(strippedAttr, difficulty.HPDrainRate);
        }
        else if(attrName == "CircleSize")
        {
            setAttr<float>(strippedAttr, difficulty.circleSize);
            difficulty.circleSizePx = (23.05f - (difficulty.circleSize - 7.0f) * 4.4825f) * 2.0f * window::get_oxu_px();
        }
        else if(attrName == "OverallDifficulty")
        {
            setAttr<float>(strippedAttr, difficulty.overallDifficulty);
        }
        else if(attrName == "ApproachRate")
        {
            setAttr<float>(strippedAttr, difficulty.approachRate);
            difficulty.approachRateMs = difficulty.approachRate <= 5 ? 1800 - difficulty.approachRate * 120 : 1200 - (difficulty.approachRate - 5) * 150;
        }
        else if(attrName == "SliderMultiplier")
        {
            setAttr<float>(strippedAttr, difficulty.sliderMultiplier);
        }
        else if(attrName == "SliderTickRate")
        {
            setAttr<float>(strippedAttr, difficulty.sliderTickRate);
        }
    }

    static uint8_t getParsedHitObjectType(uint8_t &type)
    {
        if( type  & (1 << 0) )
        {
            return Types::CIRCLE;
        }
        else if( type & (1 << 1) )
        {
            return Types::SLIDER;
        }

        return Types::SPINNER;
    }

    static bool parseControlPoints(const std::string &line, std::vector<Vector2<float>> &controlPoints)
    {
        std::string strX = "", strY = "";
        float x, y;
        bool readX = true;
        
        if(line[1] != '|')
        {
            return false;
        }

        for(size_t i = 2; i < line.size(); ++i)
        {
            if(line[i] == ':')
            {
                readX = false;
            }
            else if(line[i] == '|')
            {
                readX = true;

                if(!setAttr<float>(strX, x) || !setAttr<float>(strY, y))
                {
                    return false;
                }
                controlPoints.emplace_back(x, y);

                strX = "";
                strY = "";
            }
            else
            {
                if(readX)
                {
                    strX += line[i];
                }
                else
                {
                    strY += line[i];
                }
            }
        }

        if(!setAttr<float>(strX, x) || !setAttr<float>(strY, y))
        {
            return false;
        }
        controlPoints.emplace_back(x, y);

        return true;
    }

    static void logWarnInvalidObject(const std::string &line)
    {
        OXU_LOG_WARN("Skipped invalid object {0}", line);
    }

#define OBJ_X 0
#define OBJ_Y 1
#define OBJ_HIT_TIME 2
#define OBJ_TYPE 3
#define OBJ_HIT_SOUND 4
#define OBJ_PARAMS 5
#define SLIDER_REPEATS 6
#define SLIDER_EXPECTED_LEN 7

    void parseAndAddHitObject(const std::string &line, std::vector<std::unique_ptr<HitObject>> &hitObjects, const PlayField &playField, const Difficulty &difficulty)
    {
        std::vector<std::string> objInfo = getSplitStr(line, ',');

        if(objInfo.size() < 6)
        {
            logWarnInvalidObject(line);
            return;
        }

        Vector2<float> position;
        if(!setAttr<float>(objInfo[OBJ_X], position.x) || !setAttr<float>(objInfo[OBJ_Y], position.y))
        {
            logWarnInvalidObject(line);
            return;
        }

        uint32_t hitTime;
        uint8_t type;
        if(!setAttr<uint32_t>(objInfo[OBJ_HIT_TIME], hitTime) || !setAttr<uint8_t>(objInfo[OBJ_TYPE], type))
        {
            logWarnInvalidObject(line);
            return;
        }

        /* scale the position */
        position = playField.getStartPoint() + position * window::get_oxu_px();

        type = getParsedHitObjectType(type);

        switch(type)
        {
        case Types::CIRCLE:
            hitObjects.emplace_back(std::make_unique<HitCircle>(
                position, 
                hitTime, 
                type, 
                difficulty
            ));
            break;

        case Types::SLIDER:
            {
                std::string objParams = objInfo[OBJ_PARAMS];
                char sType;

                // Linear Bezier PerfectCircle
                if(!strchr("LBP", objParams[0]))
                {
                    logWarnInvalidObject(line);
                    return;
                }

                sType = objParams[0];

                int repeats;
                double expectedLength;

                if(
                    !setAttr<int>(objInfo[SLIDER_REPEATS], repeats) || 
                    !setAttr<double>(objInfo[SLIDER_EXPECTED_LEN], expectedLength)
                  )
                {
                    logWarnInvalidObject(line);
                    return;
                }

                std::vector<Vector2<float>> controlPoints;

                if(!parseControlPoints(objParams, controlPoints))
                {
                    logWarnInvalidObject(line);
                    return;
                }

                hitObjects.emplace_back(std::make_unique<Slider>(
                    position,
                    hitTime,
                    type,
                    controlPoints,
                    sType,
                    repeats,
                    expectedLength,
                    difficulty
                ));
            }
            break;

        case Types::SPINNER:
            break;
        }
    }
}
