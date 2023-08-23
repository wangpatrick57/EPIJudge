#include "test_framework/generic_test.h"
#include <iostream>

short Parity(unsigned long long x)
{
    short parity = 0;

    while (x) {
        unsigned long long lowest_bit = x & ~(x - 1);
        x = x & ~lowest_bit;
        parity = !parity;
    }

    return parity;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                           DefaultComparator{}, param_names);
}
