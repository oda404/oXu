// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<math.h>

namespace oxu
{
    template<typename T>
    class Vector2
    {
    private:
        T values[2];

    public:
        Vector2() { }

        Vector2(const T &firstV, const T &secondV)
        {
            values[0] = firstV;
            values[1] = secondV;
        }

        const T &getX() const { return values[0]; }
 
        const T &getY() const { return values[1]; }

        void setVector(const T &firstV, const T &secondV)
        {
            values[0] = firstV;
            values[1] = secondV;
        }

        /* Index can only be 0 or 1 else you're going to get an out of bounds */
        T &operator[](const unsigned int &i) { return values[i]; }

        void operator=(const Vector2<T> &newVec)
        {
            values[0] = newVec.getX();
            values[1] = newVec.getY();
        }

        const bool operator==(const Vector2<T> &compVec) const
        {
            return values[0] == compVec.getX() && 
                   values[1] == compVec.getY() ?  true : false;
        }

        void operator+=(const Vector2<T> &pVec)
        {
            values[0] += pVec.getX();
            values[1] += pVec.getY();
        }

        void operator-=(const Vector2<T> &pVec)
        {
            values[0] -= pVec.getX();
            values[1] -= pVec.getY();
        }

        const Vector2 operator+(const Vector2<T> &pVec) const
        {
            Vector2 result = *this;
            result += pVec;

            return result;
        }

        const Vector2 operator-(const Vector2<T> &pVec) const
        {
            Vector2 result = *this;
            result -= pVec;
            
            return result;
        }

        void operator*=(const T &n)
        {
            values[0] *= n;
            values[1] *= n;
        }

        const Vector2 operator*(const T &n) const
        {
            Vector2 result = *this;
            result *= n;

            return result;
        }

        void operator/=(const T &n)
        {
            values[0] /= n;
            values[1] /= n;
        }

        const Vector2 operator/(const T &n) const
        {
            Vector2 result = *this;
            result /= n;

            return result;
        }

        const bool operator!=(const Vector2<T> &pVec) const
        {
            if(*this == pVec)
            {
                return false;
            }

            return true;
        }
    };
}
