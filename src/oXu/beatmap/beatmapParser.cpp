#include"beatmapParser.hpp"

#include<sstream>

#include<oXu/core/scaling.hpp>
#include<oXu/utils/logger.hpp>

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

    void parseGeneral(const std::string &line, General &general)
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

    void parseEditor(const std::string &line, Editor &editor)
    {
        
    }

    void parseMetadata(const std::string &line, Metadata &metadata)
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

    void parseDifficulty(const std::string &line, Difficulty &difficulty)
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
            difficulty.circleSizePx = (23.05f - (difficulty.circleSize - 7.0f) * 4.4825f) * 2.0f * Scaling::oxuPx;
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

    void parseEvents(const std::string &line, Events &events)
    {

    }

    void parseTimingPoints(const std::string &line, std::vector<TimingPoint> &timingPoints)
    {
        //LOG_DEBUG(line);
    }

    void parseColors(const std::string &line, std::vector<Color> &colors)
    {

    }

    #define X 0
    #define Y 1
    #define HIT_TIME 2
    #define TYPE 3
    #define HIT_SOUND 4
    #define PARAMS 5

    void parseObjects(const std::string &line, std::vector<HitObject> &hitObjects, const PlayField &playField, const Difficulty &difficulty)
    {
        std::vector<std::string> strInfo = getSplitStr(line, ',');

        if(strInfo.size() < 6)
        {
            LOG_WARN("Skipped object {0} since it's invalid.", line);
            return;
        }

        Vector2<float> pos;
        uint32_t hitTime;
        uint8_t type;

        if(!setAttr<float>(strInfo[X], pos.x) || !setAttr<float>(strInfo[Y], pos.y))
        {
            LOG_WARN("Skipped object {0} since it's invalid.", line);
            return;
        }

        if(!setAttr<uint32_t>(strInfo[HIT_TIME], hitTime) || !setAttr<uint8_t>(strInfo[TYPE], type))
        {
            LOG_WARN("Skipped object {0} since it's invalid.", line);
            return;
        }

        hitObjects.emplace_back(pos, hitTime, type, playField, difficulty);
    }
}
