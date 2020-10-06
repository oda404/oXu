#pragma once

#include<cstdint>
#include<vector>

namespace oxu
{
    struct Image
    {
    private:
        std::vector<unsigned char> m_buffer;
        uint32_t m_width;
        uint32_t m_height;
        int m_BPP;
        int m_colorType;

    public:
        inline std::vector<unsigned char> &getBuffer()
        {
            return m_buffer;
        }

        inline const uint32_t &getWidth() const
        {
            return m_width;
        }

        inline const uint32_t &getHeight() const
        {
            return m_height;
        }

        inline const int &getBPP() const
        {
            return m_BPP;
        }

        inline const int &getColorType() const
        {
            return m_colorType;
        }

        bool load(const char *path);
    };
}