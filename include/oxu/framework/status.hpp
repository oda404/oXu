// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<cstdint>

namespace oxu::framework::status
{
    enum Codes
    {
        OK,
        FRAMEWORK_INIT_FAIL,
        WINDOW_INIT_FAIL,
        RENDERER_INIT_FAIL,
    };
    void set(uint8_t code);
    const uint8_t &get();
}
