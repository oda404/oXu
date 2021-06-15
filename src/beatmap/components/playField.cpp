// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/beatmap/components/playField.hpp>
#include<oxu/core/window.hpp>

oxu::PlayField::PlayField()
{
    startPoint = { 
        window::get_window_size().x / 2.f - 256.f * window::get_oxu_px(), 
        window::get_window_size().y / 2.f - 192.f * window::get_oxu_px() 
    };
}
