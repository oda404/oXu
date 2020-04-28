// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<cstdint>

#include"../oxuUtils/vector2.hpp"

namespace oxu
{
	class HitCircle
    {
    private:
        Vector2i position;
        const uint32_t spawnTime; // in millis

    public:
        HitCircle(const Vector2i &p_position, const uint32_t &p_spawnTime);
    };
}
