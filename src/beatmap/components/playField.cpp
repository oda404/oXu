// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/beatmap/components/playField.hpp>
#include<oxu/framework/window.hpp>
#include<oxu/framework/window.hpp>

namespace oxu
{

using namespace framework;

PlayField::PlayField()
    : m_oxu_px(window::get_window_size().y / 480.f)
{
    startPoint = { 
        window::get_window_size().x / 2.f - 256.f * m_oxu_px, // FIXME 
        window::get_window_size().y / 2.f - 192.f * m_oxu_px  // FIXME
    };
}

const float &PlayField::get_oxu_px() const
{
    return m_oxu_px;
}

}
