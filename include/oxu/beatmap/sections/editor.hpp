#pragma once

#include<vector>

namespace oxu
{
    enum class EditorField
    {
        BOOKMARKS = 0,
        DISTANCE_SPACING = 1,
        BEAT_DIVISOR = 2,
        GRID_SIZE = 3,
        TIMELINE_ZOOM = 4,
        INVALID = 255
    };

    struct Editor
    {
        std::vector<int> bookmarks;
        float distanceSpacing;
        float beatDivisor;
        int gridSize;
        float timelineZoom;
    };
}
