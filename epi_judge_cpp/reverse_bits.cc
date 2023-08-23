#include "test_framework/generic_test.h"
#include <limits.h>
#include <iostream>
#include <bitset>

using namespace std;

unsigned long long ReverseBits(unsigned long long x)
{
    unsigned long long reverse = 0ULL;
    int x_index = 0;
    const size_t ull_num_bits = sizeof(unsigned long long) * CHAR_BIT;

    while (x_index < ull_num_bits) {
        unsigned long long x_mask = 1ULL << x_index;
        unsigned long long x_bit = x & x_mask;

        if (x_bit) {
            int reverse_index = ull_num_bits - 1 - x_index;
            int left_shift_amount = reverse_index - x_index;
            unsigned long long reverse_bit;

            if (left_shift_amount == 0) {
                reverse_bit = x_bit;
            } else if (left_shift_amount > 0) {
                reverse_bit = x_bit << left_shift_amount;
            } else {
                reverse_bit = x_bit >> -left_shift_amount;
            }

            reverse |= reverse_bit;
        }

        x_index++;
    }

    return reverse;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                           &ReverseBits, DefaultComparator{}, param_names);
}
