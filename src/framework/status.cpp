// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/framework/status.hpp>

namespace oxu::framework
{
    static uint8_t c_status_code;

    void status::set(uint8_t code)
    {
        c_status_code = code;
    }

    const uint8_t &status::get()
    {
        return c_status_code;
    }
}
