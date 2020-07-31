#pragma once

#include<vector>

namespace oxu
{
    struct Editor
    {
        std::vector<int> bookmarks;
        float distanceSpacing;
        float beatDivisor;
        int gridSize;
        float timelineZoom;
    };
}
