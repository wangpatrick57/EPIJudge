#include <vector>
#include <iostream>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n)
{
    vector<bool> is_prime(n + 1, true);
    int n_sqrt = sqrt(n);

    for (int num = 2; num <= n; num++) {
        if (is_prime[num]) {
            // sieve from num * num because all lesser multiples of num have already been sieved
            if (num <= n_sqrt) { // conditional to avoid int overflow
                for (int composite_num = num * num; composite_num <= n; composite_num += num) {
                    is_prime[composite_num] = false;
                }
            }
        }
    }

    vector<int> primes;

    for (int num = 2; num <= n; num++) {
        if (is_prime[num]) {
            primes.push_back(num);
        }
    }

    return primes;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"n"};
    return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                           &GeneratePrimes, DefaultComparator{}, param_names);
}
