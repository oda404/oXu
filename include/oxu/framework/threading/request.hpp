#pragma once

#include<cstdint>
#include<vector>
#include<string>

namespace oxu::framework::threading
{
    struct Graphics
    {
        enum
        {
            HALT_THREAD = 1,

        };
    };

    struct Audio
    {
        enum
        {
            HALT_THREAD = 1,
        };
    };

    struct Request
    {
    public:
        Request(uint8_t p_instruction);
        Request();

        uint8_t instruction = 0;
    };
}
