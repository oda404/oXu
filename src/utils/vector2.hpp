#pragma once

namespace oxu
{
    struct Vector2f
    {
        float x, y;
        Vector2f();
        Vector2f(const float &x, const float &y);

        const Vector2f operator*(const float &n) const;

        const Vector2f operator+(const Vector2f &v) const;
    };

    struct Vector2i
    {
        int x, y;
        Vector2i();
        Vector2i(const int &x, const int &y);
        
    };
}