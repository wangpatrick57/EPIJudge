#include "test_framework/generic_test.h"

short CountBits(unsigned int x)
{
    int num_ones = 0;

    while (x != 0) {
        if ((x & 1) != 0) {
            num_ones++;
        }

        x >>= 1;
    }

    return num_ones;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                           DefaultComparator{}, param_names);
}
