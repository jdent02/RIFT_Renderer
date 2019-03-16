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

#include "drand48.h"

#include <cmath>

void DRand48::seed_gen(const uint64_t seed)
{
    rand48_seed[0] = RAND48_SEED_0;
    rand48_seed[1] = static_cast<unsigned short>(seed);
    rand48_seed[2] = static_cast<unsigned short>(seed >> 16);
    rand48_mult[0] = RAND48_MULT_0;
    rand48_mult[1] = RAND48_MULT_1;
    rand48_mult[2] = RAND48_MULT_2;
    rand48_add = RAND48_ADD;
}

double DRand48::erand48(unsigned short* xseed)
{
    dorand48(xseed);
    return ldexp(static_cast<double>(xseed[0]), -48) +
           ldexp(static_cast<double>(xseed[1]), -32) +
           ldexp(static_cast<double>(xseed[2]), -16);
}

void DRand48::dorand48(unsigned short* xseed)
{
    unsigned short temp[2];

    unsigned long accu = static_cast<unsigned long>(rand48_mult[0]) *
                             static_cast<unsigned long>(xseed[0]) +
                         static_cast<unsigned long>(rand48_add);
    temp[0] = static_cast<unsigned short>(accu); /* lower 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += static_cast<unsigned long>(rand48_mult[0]) *
                static_cast<unsigned long>(xseed[1]) +
            static_cast<unsigned long>(rand48_mult[1]) *
                static_cast<unsigned long>(xseed[0]);
    temp[1] = static_cast<unsigned short>(accu); /* middle 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += rand48_mult[0] * xseed[2] + rand48_mult[1] * xseed[1] +
            rand48_mult[2] * xseed[0];
    xseed[0] = temp[0];
    xseed[1] = temp[1];
    xseed[2] = static_cast<unsigned short>(accu);
}
