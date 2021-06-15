#pragma once

#include<string>
#include<vector>
#include<cstdint>
#include<memory>
#include<unordered_map>
#include<mutex>

#include<oxu/beatmap/sections/general.hpp>
#include<oxu/beatmap/sections/editor.hpp>
#include<oxu/beatmap/sections/metadata.hpp>
#include<oxu/beatmap/sections/difficulty.hpp>

#include<oxu/skin/skin.hpp>
#include<oxu/beatmap/components/hitObject.hpp>

#include<oxu/utils/timer.hpp>

namespace oxu
{
    class Beatmap
    {
    private:
        std::uint8_t m_file_version;
        std::string m_path;
        std::vector<std::unique_ptr<HitObject>> m_hit_objs;
        std::vector<HitObject*> m_active_hit_objs;
        std::uint32_t m_current_obj_i = 0;
        Timer m_timer;
        General m_general;
        Editor m_editor;
        Metadata m_metadata;
        Difficulty m_difficulty;

    public:
        Beatmap(const std::string &path_p);

        void loadGeneralSection();
        void loadEditorSection();
        void loadMetadataSection();
        void loadDifficultySection();
        void loadHitObjects();
        void loadAllSections();
        void updateObjects(const double &delta);
        void renderObjects(const Skin &skin);
        void start();

        inline const std::string &getPath() const
        {
            return m_path;
        }

        inline const General &getGeneralSection() const
        {
            return m_general;
        }

        inline const Editor &getEditorSection() const
        {
            return m_editor;
        }

        inline const Metadata &getMetadataSection() const
        {
            return m_metadata;
        }

        inline const Difficulty &getDifficulty() const
        {
            return m_difficulty;
        }
    };
}
