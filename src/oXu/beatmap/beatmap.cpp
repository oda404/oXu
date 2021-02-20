#include "beatmap.hpp"

#include<fstream>
#include<mutex>

#include<oXu/beatmap/beatmapParser.hpp>
#include<oXu/beatmap/sections/config.hpp>
#include<oXu/beatmap/components/playField.hpp>
#include<oXu/core/logger.hpp>

namespace oxu
{
    static std::mutex c_beatmap_mtx;

    static void setSection(const std::string &line, uint8_t &section)
    {
        std::map<std::string, std::uint8_t>::const_iterator pair = sectionsMap.find(line);

        if(pair->first != "")
        {
            section = pair->second;
        }
    }

    Beatmap::Beatmap(const std::string &path_p):
    m_path(path_p)
    {

    }

    void Beatmap::start()
    {
        m_current_obj_i = 0;
        m_active_hit_objs.clear();
        m_timer.start();
    }

    void Beatmap::updateObjects(const double &delta)
    {
        const std::uint32_t ellapsedMs = m_timer.getEllapsedMs();

        c_beatmap_mtx.lock();
        while(m_hit_objs[m_current_obj_i]->shouldBeAddedToPool(ellapsedMs))
        {
            m_active_hit_objs.push_back(m_hit_objs[m_current_obj_i].get());
            ++m_current_obj_i;
        }
        
        while(
            m_active_hit_objs.size() > 0 && 
            m_active_hit_objs[0]->shouldBeRemovedFromPool()
        )
        {
            m_active_hit_objs.erase(m_active_hit_objs.begin());
        }

        for(HitObject *ho: m_active_hit_objs)
        {
            ho->update(delta, difficulty);
        }
        c_beatmap_mtx.unlock();
    }

    void Beatmap::renderObjects(const Skin &skin)
    {
        c_beatmap_mtx.lock();
        std::uint32_t i = m_active_hit_objs.size(); 
        for(; i > 0; --i)
        {
            m_active_hit_objs[i - 1]->render(skin);
        }
        c_beatmap_mtx.unlock();
    }

    void Beatmap::loadGenericInfo()
    {
        std::ifstream beatmapFile(m_path);

        if(beatmapFile.is_open())
        {
            std::string line;
            uint8_t section = SECTIONS_COUNT;

            while(std::getline(beatmapFile, line))
            {
                if(line[0] == '[')
                {
                    if(section == Sections::DIFFICULTY)
                    {
                        break;
                    }

                    setSection(line, section);
                }
                else if(line[0] != '\r')
                {
                    switch(section)
                    {
                    case Sections::GENERAL:
                        parseAndSetGeneral(line, general);
                        break;

                    case Sections::METADATA:
                        parseAndSetMetadata(line, metadata);
                        break;

                    case Sections::DIFFICULTY:
                        parseAndSetDifficulty(line, difficulty);
                        break;
                    }
                }
            }

            beatmapFile.close();
        }
        else
        {
            OXU_LOG_WARN("Could not open file {0}", m_path);
        }
    }

    void Beatmap::loadGameInfo()
    {
        std::ifstream beatmapFile(m_path);

        if(beatmapFile.is_open())
        {
            m_hit_objs.clear();
            /* hardcoded value for now */
            m_hit_objs.reserve(4000);

            std::string line;
            uint8_t section = SECTIONS_COUNT;
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
                        case Sections::TIMING:

                            break;

                        case Sections::OBJECTS:
                            parseAndAddHitObject(line, m_hit_objs, playField, difficulty);
                            break;
                    }
                }
            }

            beatmapFile.close();
        }
        else
        {
            OXU_LOG_WARN("Could not open file {0}", m_path);
        }
    }

    const std::string &Beatmap::getPath()
    {
        return m_path;
    }
}
