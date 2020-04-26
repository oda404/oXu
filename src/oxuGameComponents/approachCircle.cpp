// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"approachCircle.hpp"

oxu::ApproachCircle::ApproachCircle(const Vector2i &spawnPos, const Vector2i &texSize):
halfTex_x(texSize.x / 2), halfTex_y(texSize.y / 2)
{
    /* Set the origin in the middle of the sprite */
    ac_rect.w = texSize.x;
    ac_rect.h = texSize.y;

    ac_rect.x = spawnPos.x - halfTex_x;
    ac_rect.y = spawnPos.y - halfTex_y;
}

const SDL_Rect *oxu::ApproachCircle::getSDLRect()
{
    return &ac_rect;
}

void oxu::ApproachCircle::move(Vector2i pos)
{
    ac_rect.x = pos.x - halfTex_x;
    ac_rect.y = pos.y - halfTex_y;
}
