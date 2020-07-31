#include"beatmapParser.hpp"

namespace oxu
{
    static std::string getAttribute(const std::string &line)
    {
        std::string result = line.substr(line.find_first_of(':') + 1, line.size());
        if(result[0] == ' ')
        {
            result.erase(0, 1);
        }

        return result;
    }

    static std::string parseAttributeStr(const std::string &line)
    {
        return getAttribute(line);
    }

    static int parseAttributeInt(const std::string &line)
    {
        return std::stoi(getAttribute(line));
    }

    static float parseAttributeFloat(const std::string &line)
    {
        return std::stof(getAttribute(line));
    }

    static std::string parseAttributeName(const std::string &line)
    {
        return line.substr(0, line.find_first_of(':'));
    }

    static std::vector<std::string> split(const std::string &line, const char &ch)
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

    void parseGeneral(const std::string &line, General &general)
    {
        /* This shit hurts my brain and it's probably pretty bad but I can't think of another way of doing it */

        std::string attrName = parseAttributeName(line);

        if(attrName == "AudioFilename")
        {
            general.audioFilename = parseAttributeStr(line);
        }
        else if(attrName == "AudioLeadIn")
        {
            general.audioLeadIn = parseAttributeInt(line);
        }
        else if(attrName == "PreviewTime")
        {
            general.previewTime = parseAttributeInt(line);
        }
        else if(attrName == "Countdown")
        {
            general.countdown = parseAttributeInt(line);
        }
        else if(attrName == "SampleSet")
        {
            general.sampleSet = parseAttributeStr(line);
        }
        else if(attrName == "StackLeniency")
        {
            general.stackLeniency = parseAttributeFloat(line);
        }
        else if(attrName == "Mode")
        {
            general.mode = parseAttributeInt(line);
        }
        else if(attrName == "LetterboxInBreaks")
        {
            general.letterboxInBreaks = parseAttributeInt(line);
        }
        else if(attrName == "WidescreenStoryboard")
        {
            general.widescreenStoryboard = parseAttributeInt(line);
        }
    }

    void parseEditor(const std::string &line, Editor &editor)
    {
        
    }

    void parseMetadata(const std::string &line, Metadata &metadata)
    {
        std::string attrName = parseAttributeName(line);

        if(attrName == "Title")
        {
            metadata.title = parseAttributeStr(line);
        }
        else if(attrName == "TitleUnicode")
        {
            metadata.titleUnicode = parseAttributeStr(line);
        }
        else if(attrName == "Artist")
        {
            metadata.artist = parseAttributeStr(line);
        }
        else if(attrName == "ArtistUnicode")
        {
            metadata.artistUnicode = parseAttributeStr(line);
        }
        else if(attrName == "Creator")
        {
            metadata.creator = parseAttributeStr(line);
        }
        else if(attrName == "Version")
        {
            metadata.version = parseAttributeStr(line);
        }
        else if(attrName == "Source")
        {
            metadata.source = parseAttributeStr(line);
        }
        else if(attrName == "Tags")
        {
            //TODO
        }
        else if(attrName == "BeatmapID")
        {
            metadata.beatmapID = parseAttributeInt(line);
        }
        else if(attrName == "BeatmapSetID")
        {
            metadata.beatmapSetID = parseAttributeInt(line);
        }
    }

    void parseDifficulty(const std::string &line, Difficulty &difficulty)
    {
        std::string attrName = parseAttributeName(line);

        if(attrName == "HPDrainRate")
        {
            difficulty.HPDrainRate = parseAttributeFloat(line);
        }
        else if(attrName == "CircleSize")
        {
            difficulty.circleSize = parseAttributeFloat(line);
            difficulty.circleSizePx = (23.05f - (difficulty.circleSize - 7.0f) * 4.4825f) * 2.0f * Scaling::oxuPx;
        }
        else if(attrName == "OverallDifficulty")
        {
            difficulty.overallDifficulty = parseAttributeFloat(line);
        }
        else if(attrName == "ApproachRate")
        {
            difficulty.approachRate = parseAttributeFloat(line);
            difficulty.approachRateMs = difficulty.approachRate <= 5 ? 1800 - difficulty.approachRate * 120 : 1200 - (difficulty.approachRate - 5) * 150;
        }
        else if(attrName == "SliderMultiplier")
        {
            difficulty.sliderMultiplier = parseAttributeFloat(line);
        }
        else if(attrName == "SliderTickRate")
        {
            difficulty.sliderTickRate = parseAttributeFloat(line);
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

    void parseObjects(const std::string &line, std::vector<HitObject> &hitObjects, const PlayField &playField, const Difficulty &difficulty)
    {
        // TODO: check if parsed info is valid
        std::vector<std::string> info = split(line, ',');

        hitObjects.emplace_back(Vector2<float>(std::stoi(info[0]), std::stoi(info[1])), std::stoi(info[2]), std::stoi(info[3]), playField, difficulty);
    }
}
