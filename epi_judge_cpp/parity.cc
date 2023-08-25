#include "test_framework/generic_test.h"
#include <iostream>

static char parity_cache[1 << 16];

static char compute_short_parity(unsigned short x) {
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return (char)(x & 1);
}

static char get_short_parity(unsigned short x, char *parity_cache) {
    if (parity_cache[x] == -1) {
        parity_cache[x] = compute_short_parity(x);
    }

    return parity_cache[x];
}

short Parity(unsigned long long x)
{
    char q1_parity = get_short_parity((unsigned short)x, parity_cache);
    x >>= 16;
    char q2_parity = get_short_parity((unsigned short)x, parity_cache);
    x >>= 16;
    char q3_parity = get_short_parity((unsigned short)x, parity_cache);
    x >>= 16;
    char q4_parity = get_short_parity((unsigned short)x, parity_cache);
    char parity = q1_parity ^ q2_parity ^ q3_parity ^ q4_parity;

    return (short)parity;
}

int main(int argc, char *argv[])
{
    memset(parity_cache, -1, 1 << 16);
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                           DefaultComparator{}, param_names);
}
