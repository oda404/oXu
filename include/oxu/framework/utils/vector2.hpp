// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<cmath>
#include<string>

namespace oxu::framework
{
    template<typename T>
    class Vector2
    {
    public:
        T x, y;

        constexpr Vector2()
        {

        }

        constexpr Vector2(const T &x, const T &y)
        :x(x), y(y)
        {
            
        }

        /* Sets the x, y values of the vector to the specified ones. */
        void setVector(const T &x, const T &y)
        {
            this->x = x;
            this->y = y;
        }

        /* Returns the vector's length(magnitude). */
        constexpr float getLength() const
        {
            return static_cast<float>(std::sqrt(x * x + y * y));
        }

        /* Returns the vector's length(magnitude) squared. */
        constexpr float getLengthSquared() const
        {
            return static_cast<float>(x * x + y * y);
        }

        /* Normalizes the vector. */
        void normalize()
        {
            *this /= this->getLength();
        }

        /* Returns a normalized version of the vector. This doesn't modify the base vector */
        constexpr Vector2<T> normalized() const
        {
            Vector2<T> result = *this;
            result /= this->getLength();

            return result;
        }

        /* Clamps the vector's x, y to the specified values */
        void clamp(const T &min, const T &max)
        {
            x = x < min ? min : x;
            x = x > max ? max : x;

            y = y < min ? min : y;
            y = y > max ? max : y;
        }

        /* Returns a clamped version of the vector. This doesn't modify the base vector */
        constexpr Vector2<T> clamped(const T &min, const T &max) const
        {
            Vector2<T> result = *this;

            result.x = result.x < min ? min : result.x;
            result.x = result.x > max ? max : result.x;

            result.y = result.y < min ? min : result.y;
            result.y = result.y > max ? max : result.y;

            return result;
        }

        constexpr static Vector2<T> lerp(const Vector2<T> &start, const Vector2<T> &end, const float &t)
        {
            return start * (1 - t) + end * t;
        }

        /* Returns the vector formatted as a string */
        constexpr std::string toString() const
        {
            std::string result = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
            return result;
        }

        void operator+=(const Vector2<T> &v)
        {
            x += v.x;
            y += v.y;
        }

        constexpr Vector2<T> operator+(const Vector2<T> &v) const
        {
            Vector2<T> result = *this;
            result += v;

            return result;
        }

        void operator+=(const T &n)
        {
            x += n;
            y += n;
        }

        constexpr Vector2<T> operator+(const T &n) const
        {
            Vector2<T> out = *this;

            out.x += n;
            out.y += n;
            
            return out;
        }

        void operator-=(const Vector2<T> &v)
        {
            x -= v.x;
            y -= v.y;
        }

        constexpr Vector2<T> operator-(const Vector2<T> &v) const
        {
            Vector2<T> result = *this;
            result -= v;

            return result;
        }

        void operator*=(const T &n)
        {
            x *= n;
            y *= n;
        }

        constexpr Vector2<T> operator*(const T &n) const
        {
            Vector2<T> result = *this;
            result *= n;

            return result;
        }

        void operator/=(const T &n)
        {
            x /= n;
            y /= n;
        }

        constexpr Vector2<T> operator/(const T &n) const
        {
            Vector2<T> result = *this;
            result /= n;

            return result;
        }

        constexpr bool operator==(const Vector2<T> &v) const
        {
            return x == v.x && y == v.y;
        }

        constexpr bool operator!=(const Vector2<T> &v) const
        {
            return !(*this == v);
        }
    };

    template<typename T>
    Vector2<T> operator+(T n, const Vector2<T> &v)
    {
        return v + n;
    }
}
