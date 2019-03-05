#include "drand48.h"

#include <cmath>


void drand_48::seed_gen(uint64_t seed)
{
    rand48_seed[0] = RAND48_SEED_0;
    rand48_seed[1] = static_cast<unsigned short>(seed);
    rand48_seed[2] = static_cast<unsigned short>(seed >> 16);
    rand48_mult[0] = RAND48_MULT_0;
    rand48_mult[1] = RAND48_MULT_1;
    rand48_mult[2] = RAND48_MULT_2;
    rand48_add = RAND48_ADD;
}

double drand_48::erand48(unsigned short* xseed)
{
    dorand48(xseed);
    return ldexp(static_cast<double>(xseed[0]), -48) +
        ldexp(static_cast<double>(xseed[1]), -32) +
        ldexp(static_cast<double>(xseed[2]), -16);
}

void drand_48::dorand48(unsigned short* xseed)
{
    unsigned short temp[2];

    unsigned long accu =
        (unsigned long)rand48_mult[0] * static_cast<unsigned long>(xseed[0]) + static_cast<unsigned long>(rand48_add);
    temp[0] = static_cast<unsigned short>(accu); /* lower 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += static_cast<unsigned long>(rand48_mult[0]) * static_cast<unsigned long>(xseed[1]) +
        static_cast<unsigned long>(rand48_mult[1]) * static_cast<unsigned long>(xseed[0]);
    temp[1] = static_cast<unsigned short>(accu); /* middle 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += rand48_mult[0] * xseed[2] + rand48_mult[1] * xseed[1] + rand48_mult[2] * xseed[0];
    xseed[0] = temp[0];
    xseed[1] = temp[1];
    xseed[2] = static_cast<unsigned short>(accu);
}
