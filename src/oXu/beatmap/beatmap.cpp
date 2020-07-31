#include "beatmap.hpp"

namespace oxu
{
    static void setSection(const std::string &line, uint8_t &section)
    {
        section = sectionsMap.find(line)->second;
    }

    Beatmap::Beatmap(const std::string &path_p):
    path(path_p)
    {

    }

    void Beatmap::loadGenericInfo()
    {
        std::ifstream beatmapFile(path);
        std::string line;

        uint8_t section = 9;

        while(std::getline(beatmapFile, line))
        {
            if(line[0] == '[')
            {
                if(section == DIFFICULTY_SECTION)
                {
                    break;
                }

                setSection(line, section);
            }
            else if(line[0] != '\r')
            {
                switch(section)
                {
                    case GENERAL_SECTION:
                        parseGeneral(line, general);
                        break;

                    case METADATA_SECTION:
                        parseMetadata(line, metadata);
                        break;

                    case DIFFICULTY_SECTION:
                        parseDifficulty(line, difficulty);
                        break;
                }
            }
        }

        beatmapFile.close();
    }

    void Beatmap::loadGameInfo()
    {
        std::ifstream beatmapFile(path);
        std::string line;
        uint8_t section = 9;

        PlayField playField;

        while(std::getline(beatmapFile, line))
        {
            if(line[0] == '[')
            {
                setSection(line, section);
            }
            else if(line[0] != '\r')
            {
                switch(section)
                {
                    case TIMING_SECTION:
                        parseTimingPoints(line, timingPoints);
                        break;

                    case OBJECTS_SECTION:
                        parseObjects(line, hitObjects, playField, difficulty);
                        break;
                }
            }
        }

        beatmapFile.close();
    }
}
