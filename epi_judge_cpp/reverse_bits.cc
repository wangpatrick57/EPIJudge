#include "test_framework/generic_test.h"
#include <limits.h>
#include <iostream>
#include <bitset>

using namespace std;
const int SHORT_NUM_BITS = 16;
const int ULL_NUM_BITS = 64;
unsigned short reversed_cache[1 << SHORT_NUM_BITS];

static unsigned short swap_bits(unsigned short x, int i, int j) {
    unsigned short inverted_x = x ^ (1 << i) ^ (1 << j);
    bool x_should_be_inverted = ((x >> i) & 1) != ((x >> j) & 1);
    unsigned short res = x_should_be_inverted ? inverted_x : x;
    return res;
}

static unsigned short compute_reversed_short(unsigned short x) {
    for (int i = 0; i < SHORT_NUM_BITS / 2; i++) {
        x = swap_bits(x, i, SHORT_NUM_BITS - 1 - i);
    }

    return x;
}

static unsigned short get_reversed_short(unsigned short x) {
    if (reversed_cache[x] == 0) {
        // a cache value of 0 means "invalid", unless x == 0, in which case it's valid
        if (x != 0) {
            reversed_cache[x] = compute_reversed_short(x);
        }
    }

    return reversed_cache[x];
}

static unsigned long long get_reversed_short_in_ull(unsigned long long x, int offset, unsigned long long short_mask) {
    unsigned long long res = (unsigned long long)get_reversed_short((unsigned short)((x >> offset) & short_mask)) << (ULL_NUM_BITS - SHORT_NUM_BITS - offset);
    bitset<ULL_NUM_BITS> x_binrep(x);
    bitset<ULL_NUM_BITS> res_binrep(res);
    return res;
}

unsigned long long ReverseBits(unsigned long long x)
{
    unsigned long long short_mask = (1ULL << SHORT_NUM_BITS) - 1ULL;
    return get_reversed_short_in_ull(x, 0 * SHORT_NUM_BITS, short_mask) |
        get_reversed_short_in_ull(x, 1 * SHORT_NUM_BITS, short_mask) |
        get_reversed_short_in_ull(x, 2 * SHORT_NUM_BITS, short_mask) |
        get_reversed_short_in_ull(x, 3 * SHORT_NUM_BITS, short_mask);
}

int main(int argc, char *argv[])
{
    memset(reversed_cache, 0, 1 << SHORT_NUM_BITS);
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                           &ReverseBits, DefaultComparator{}, param_names);
}
