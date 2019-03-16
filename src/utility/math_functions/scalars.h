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

template<typename T>
inline T FourOverPi()
{
    return static_cast<T>(1.2732395447351627);
} // 4 / Pi

template<typename T>
inline T FourOverPiSquare()
{
    return static_cast<T>(0.4052847345693511);
} // 1 / (4 * Pi^2)

template<typename T>
inline T RcpTwoPi()
{
    return static_cast<T>(0.1591549430918953);
} // 1 / (2 * Pi) = 0.5 / Pi

template<typename T>
inline T TwoPi()
{
    return static_cast<T>(6.2831853071795865);
} // 2 * Pi

template<typename T>
inline T HalfPi()
{
    return static_cast<T>(1.5707963267948966);
} // Pi / 2

template<typename T>
inline T TwoOverPi()
{
    return static_cast<T>(0.6366197723675813);
} // 2 / Pi

template<typename Target, typename Source>
inline Target binary_cast(Source s)
{
    static_assert(
        sizeof(Target) == sizeof(Source),
        "foundation::binary_cast() expects the source and target types to have "
        "the same size");

    union
    {
        Source m_source;
        Target m_target;
    } u;

    u.m_source = s;
    return u.m_target;
}
