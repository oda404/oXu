#pragma once

#include<string>
#include<vector>
#include<cstdint>
#include<memory>

#include<oXu/beatmap/sections/general.hpp>
#include<oXu/beatmap/sections/editor.hpp>
#include<oXu/beatmap/sections/metadata.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>

#include<oXu/skin/skin.hpp>
#include<oXu/beatmap/components/hitObject.hpp>

#include<oXu/utils/timer.hpp>

namespace oxu
{
    class Beatmap
    {
    private:
        uint8_t m_fileVersion;
        std::string m_path;

        std::vector<std::unique_ptr<HitObject>> m_hitObjects;
        std::vector<HitObject*> m_hitObjectsPool;
        uint32_t m_objI = 0;
        Timer m_timer;

    public:
        Beatmap(const std::string &path_p);

        General general;
        Editor editor;
        Metadata metadata;
        Difficulty difficulty;

        void loadGenericInfo();
        void loadGameInfo();
        void updateObjects(const double &delta);
        void renderObjects(const Skin &skin);
        void start();

        const std::string &getPath();
    };
}
