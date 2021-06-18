// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/beatmap/components/playField.hpp>
#include<oxu/framework/window.hpp>

namespace oxu
{

using namespace framework;

PlayField::PlayField()
{
    startPoint = { 
        window::get_window_size().x / 2.f - 256.f * 480, // FIXME 
        window::get_window_size().y / 2.f - 192.f * 480  // FIXME
    };
}

}
