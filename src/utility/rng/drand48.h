#ifndef DRAND_48_H
#define DRAND_48_H

#include "igenerator.h"

#include <cmath>

#define RAND48_SEED_0 0x330e
#define RAND48_SEED_1 0xabcd
#define RAND48_SEED_2 0x1234
#define RAND48_MULT_0 0xe66d
#define RAND48_MULT_1 0xdeec
#define RAND48_MULT_2 0x0005
#define RAND48_ADD 0x000b

class drand_48
    : public igenerator
{
  public:
    drand_48() = default;

    virtual ~drand_48() override = default;

    virtual float next() override { return static_cast<float>(erand48(rand48_seed)); }

    virtual void seed_gen(uint64_t seed) override;

    double erand48(unsigned short xseed[3]);

    void dorand48(unsigned short xseed[3]);

    // Properties
    unsigned short rand48_seed[3] = {RAND48_SEED_0, RAND48_SEED_1, RAND48_SEED_2};
    unsigned short rand48_mult[3] = {RAND48_MULT_0, RAND48_MULT_1, RAND48_MULT_2};
    unsigned short rand48_add = RAND48_ADD;
};

#endif // DRAND_48_H
