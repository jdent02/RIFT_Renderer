// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <cmath>
#include <iostream>

class Vec3
{
  public:
    Vec3() = default;

    Vec3(float e0, float e1, float e2);

    // Getters.
    float x() const { return m_e[0]; }

    float y() const { return m_e[1]; }

    float z() const { return m_e[2]; }

    float r() const { return m_e[0]; }

    float g() const { return m_e[1]; }

    float b() const { return m_e[2]; }

    // Operator overloads.
    const Vec3& operator+() const { return *this; }

    Vec3 operator-() const { return {-m_e[0], -m_e[1], -m_e[2]}; }

    float operator[](int i) const { return m_e[i]; }

    float& operator[](int i) { return m_e[i]; }

    Vec3& operator+=(const Vec3& v2);

    Vec3& operator-=(const Vec3& v2);

    Vec3& operator*=(const Vec3& v2);

    Vec3& operator/=(const Vec3& v2);

    Vec3& operator*=(float t);

    Vec3& operator/=(float t);

    // Other methods.
    float length() const;

    float squared_length() const;

    void make_unit_vector();

    float m_e[3]{};
};

inline std::istream& operator>>(std::istream& is, Vec3& t)
{
    is >> t.m_e[0] >> t.m_e[1] >> t.m_e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& t)
{
    os << t.m_e[0] << " " << t.m_e[1] << " " << t.m_e[2];
    return os;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return Vec3{v1.m_e[0] + v2.m_e[0], v1.m_e[1] + v2.m_e[1], v1.m_e[2] + v2.m_e[2]};
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return Vec3{v1.m_e[0] - v2.m_e[0], v1.m_e[1] - v2.m_e[1], v1.m_e[2] - v2.m_e[2]};
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
    return Vec3{v1.m_e[0] * v2.m_e[0], v1.m_e[1] * v2.m_e[1], v1.m_e[2] * v2.m_e[2]};
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
    return Vec3{v1.m_e[0] / v2.m_e[0], v1.m_e[1] / v2.m_e[1], v1.m_e[2] / v2.m_e[2]};
}

inline Vec3 operator*(const float t, const Vec3& v)
{
    return Vec3{t * v.m_e[0], t * v.m_e[1], t * v.m_e[2]};
}

inline Vec3 operator/(const Vec3& v, float const t)
{
    return Vec3{v.m_e[0] / t, v.m_e[1] / t, v.m_e[2] / t};
}

inline Vec3 operator*(const Vec3& v, const float t)
{
    return Vec3{v.m_e[0] * t, v.m_e[1] * t, v.m_e[2] * t};
}

inline Vec3& Vec3::operator+=(const Vec3& v2)
{
    m_e[0] += v2.m_e[0];
    m_e[1] += v2.m_e[1];
    m_e[2] += v2.m_e[2];
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v2)
{
    m_e[0] -= v2.m_e[0];
    m_e[1] -= v2.m_e[1];
    m_e[2] -= v2.m_e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v2)
{
    m_e[0] *= v2.m_e[0];
    m_e[1] *= v2.m_e[1];
    m_e[2] *= v2.m_e[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v2)
{
    m_e[0] /= v2.m_e[0];
    m_e[1] /= v2.m_e[1];
    m_e[2] /= v2.m_e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const float t)
{
    m_e[0] *= t;
    m_e[1] *= t;
    m_e[2] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const float t)
{
    m_e[0] /= t;
    m_e[1] /= t;
    m_e[2] /= t;
    return *this;
}

inline Vec3::Vec3(const float e0, const float e1, const float e2)
{
    m_e[0] = e0;
    m_e[1] = e1;
    m_e[2] = e2;
}

inline float Vec3::length() const
{
    return std::sqrt(m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2]);
}

inline float Vec3::squared_length() const
{
    return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
}

inline void Vec3::make_unit_vector()
{
    const float k = 1.0f / std::sqrt(m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2]);
    m_e[0] *= k;
    m_e[1] *= k;
    m_e[2] *= k;
}

inline Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2)
{
    return {(v1.m_e[1] * v2.m_e[2] - v1.m_e[2] * v2.m_e[1]),
            (-(v1.m_e[0] * v2.m_e[2] - v1.m_e[2] * v2.m_e[0])),
            (v1.m_e[0] * v2.m_e[1] - v1.m_e[1] * v2.m_e[0])};
}

inline float dot(const Vec3& v1, const Vec3& v2)
{
    return v1.m_e[0] * v2.m_e[0] + v1.m_e[1] * v2.m_e[1] + v1.m_e[2] * v2.m_e[2];
}
