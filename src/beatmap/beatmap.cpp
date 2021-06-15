
#include<fstream>
#include<mutex>
#include<oxu/beatmap/beatmap.hpp>
#include<oxu/core/window.hpp>
#include<oxu/beatmap/beatmapParser.hpp>
#include<oxu/beatmap/beatmapParser.hpp>
#include<oxu/beatmap/components/playField.hpp>
#include<oxu/core/logger.hpp>

namespace oxu
{
    static std::mutex c_beatmap_mtx;

    static float circle_size_to_px(float circle_size)
    {
        return (23.05f - (circle_size - 7.0f) * 4.4825f) * 2.0f;
    }

    static float approach_rate_to_ms(float approach_rate)
    {
        return approach_rate <= 5 ? 1800 - approach_rate * 120 : 
        1200 - (approach_rate - 5) * 150;
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
        
        std::lock_guard<std::mutex> guard(c_beatmap_mtx);
        while(m_hit_objs[m_current_obj_i]->shouldAddToPool(ellapsedMs, m_difficulty.approachRateMs))
        {
            m_active_hit_objs.push_back(m_hit_objs[m_current_obj_i].get());
            ++m_current_obj_i;
        }
        
        while(
            m_active_hit_objs.size() > 0 && 
            m_active_hit_objs[0]->shouldRemoveFromPool()
        )
        {
            m_active_hit_objs.erase(m_active_hit_objs.begin());
        }

        for(HitObject *ho: m_active_hit_objs)
        {
            ho->update(delta, m_difficulty);
        }
    }

    void Beatmap::renderObjects(const Skin &skin)
    {
        std::lock_guard<std::mutex> guard(c_beatmap_mtx);
        std::uint32_t i = m_active_hit_objs.size(); 
        for(; i > 0; --i)
        {
            m_active_hit_objs[i - 1]->render(skin);
        }
    }

    void Beatmap::loadGeneralSection()
    {
        std::ifstream beatmap_file(m_path);
        if(!beatmap_file.is_open())
        {
            OXU_LOG_WARN("Could not open beatmap file {0} for parsing.", m_path);
            return;
        }

        std::string line;
        Section section = Section::INVALID;

        while(std::getline(beatmap_file, line))
        {
            if(line[0] == '[')
            {
                section = get_section_enum_from_str(line);
                continue;
            }

            if(section == Section::GENERAL)
            {
                parse_and_set_general_field(line, m_general);
            }
        }

        beatmap_file.close();
    }

    void Beatmap::loadEditorSection()
    {
        std::ifstream beatmap_file(m_path);
        if(!beatmap_file.is_open())
        {
            OXU_LOG_WARN("Could not open beatmap file {0} for parsing.", m_path);
            return;
        }

        std::string line;
        Section section = Section::INVALID;

        while(std::getline(beatmap_file, line))
        {
            if(line[0] == '[')
            {
                section = get_section_enum_from_str(line);
                continue;
            }

            if(section == Section::EDITOR)
            {
                parse_and_set_editor_field(line, m_editor);
            }
        }

        beatmap_file.close();
    }

    void Beatmap::loadMetadataSection()
    {
        std::ifstream beatmap_file(m_path);
        if(!beatmap_file.is_open())
        {
            OXU_LOG_WARN("Could not open beatmap file {0} for parsing.", m_path);
            return;
        }

        std::string line;
        Section section = Section::INVALID;

        while(std::getline(beatmap_file, line))
        {
            if(line[0] == '[')
            {
                section = get_section_enum_from_str(line);
                continue;
            }

            if(section == Section::METADATA)
            {
                parse_and_set_metadata_field(line, m_metadata);
            }
        }

        beatmap_file.close();
    }

    void Beatmap::loadDifficultySection()
    {
        std::ifstream beatmap_file(m_path);
        if(!beatmap_file.is_open())
        {
            OXU_LOG_WARN("Could not open beatmap file {0} for parsing.", m_path);
            return;
        }

        std::string line;
        Section section = Section::INVALID;

        while(std::getline(beatmap_file, line))
        {
            if(line[0] == '[')
            {
                section = get_section_enum_from_str(line);
                continue;
            }

            if(section == Section::DIFFICULTY)
            {
                parse_and_set_difficulty_field(line, m_difficulty);
            }
        }

        beatmap_file.close();

        m_difficulty.approachRateMs = 
        approach_rate_to_ms(m_difficulty.approachRate);

        m_difficulty.circleSizePx = 
        circle_size_to_px(m_difficulty.circleSize) * window::get_oxu_px();
    }

    void Beatmap::loadHitObjects()
    {
        std::ifstream beatmap_file(m_path);
        if(!beatmap_file.is_open())
        {
            OXU_LOG_WARN("Could not open beatmap file {0} for parsing.", m_path);
            return;
        }

        std::string line;
        Section section = Section::INVALID;

        PlayField p;

        while(std::getline(beatmap_file, line))
        {
            if(line[0] == '[')
            {
                section = get_section_enum_from_str(line);
                continue;
            }

            if(section == Section::OBJECTS)
            {
                parse_and_set_hit_object(
                    line, 
                    m_hit_objs,
                    p,
                    m_difficulty
                );
            }
        }

        beatmap_file.close();
    }

    void Beatmap::loadAllSections()
    {
        loadGeneralSection();
        loadEditorSection();
        loadMetadataSection();
        loadDifficultySection();
        loadHitObjects();
    }
}
