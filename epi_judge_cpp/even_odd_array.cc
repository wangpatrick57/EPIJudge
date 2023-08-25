#include <set>
#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using namespace std;

void EvenOdd(vector<int> *A_ptr)
{
    vector<int> &A = *A_ptr;
    int n = A.size();
    int l = 0;
    int r = n - 1;

    while (true) {
        while (l < n && A[l] % 2 == 0) {
            l++;
        }

        while (r >= 0 && A[r] % 2 == 1) {
            r--;
        }

        if (l >= n || r < 0 || l >= r) {
            break;
        }

        swap(A[l], A[r]);
    }
}
void EvenOddWrapper(TimedExecutor &executor, vector<int> A)
{
    std::multiset<int> before(begin(A), end(A));

    executor.Run([&]
                 { EvenOdd(&A); });

    bool in_odd = false;
    for (int a : A)
    {
        if (a % 2 == 0)
        {
            if (in_odd)
            {
                throw TestFailure("Even elements appear in odd part");
            }
        }
        else
        {
            in_odd = true;
        }
    }

    std::multiset<int> after(begin(A), end(A));
    if (before != after)
    {
        throw TestFailure("Elements mismatch");
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "A"};
    return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                           &EvenOddWrapper, DefaultComparator{}, param_names);
}
