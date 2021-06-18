#pragma once

#include<cstdint>
#include<string>
#include<vector>

namespace oxu::framework::graphics
{
    struct Png
    {
    private:
        std::uint8_t *m_buffer = nullptr;
        std::uint32_t m_width;
        std::uint32_t m_height;
        int m_BPP;
        int m_colorType;

    public:
        Png();
        Png(const std::string &path);
        ~Png();
        const std::uint8_t *getBuffer() const;
        std::uint32_t getWidth() const;
        std::uint32_t getHeight() const;
        int getBPP() const;
        int getColorType() const;
        bool load(const std::string &path);
    };
}