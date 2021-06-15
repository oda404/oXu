// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/core/status.hpp>

namespace oxu::status
{
    static uint8_t c_status_code;

    void set(uint8_t code)
    {
        c_status_code = code;
    }

    const uint8_t &get()
    {
        return c_status_code;
    }
}
