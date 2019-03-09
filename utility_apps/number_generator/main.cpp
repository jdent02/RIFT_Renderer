

#include "utility/rng/igenerator.h"
#include "utility/rng/xoroshiro128.h"
#include <ctime>
#include <cstdio>

int main()
{
    igenerator* gen = new xoro_128;

    time_t seed = time(nullptr);

    gen->seed_gen(uint64_t(seed));

    for (int i = 0; i< 10; i++)
    {
        printf("seed: %f\n", gen->next());
    }

    return 0;
}
