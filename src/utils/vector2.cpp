#include"vector2.hpp"

oxu::Vector2f::Vector2f() { }

oxu::Vector2f::Vector2f(const float &x, const float &y):
x(x), y(y) { }

const oxu::Vector2f oxu::Vector2f::operator*(const float &n) const
{
    Vector2f result = *this;
    result.x *= n;
    result.y *= n;

    return result;
}

const oxu::Vector2f oxu::Vector2f::operator+(const Vector2f &v) const
{
    Vector2f result = *this;
    result.x += v.x;
    result.y += v.y;

    return result;
}

oxu::Vector2i::Vector2i() { }

oxu::Vector2i::Vector2i(const int &x, const int &y):
x(x), y(y) { }