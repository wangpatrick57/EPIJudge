#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

vector<int> NextPermutation(vector<int> perm)
{
    int n = perm.size();

    for (int i = n - 2; i >= 0; i--) {
        if (perm[i] < perm[i + 1]) {
            int first_drop_i = i;
            int first_drop_val = perm[first_drop_i];
            vector<int>::iterator subvec_begin = perm.begin() + first_drop_i;
            vector<int>::iterator subvec_end = perm.end();
            sort(subvec_begin, subvec_end);

            // invariant: first_drop_val will not be the largest value in the subvec
            //            this is because it's the first index where the value _decreased_
            vector<int>::iterator first_drop_new_pos = find(subvec_begin, subvec_end, first_drop_val);
            int first_drop_new_i = distance(perm.begin(), first_drop_new_pos);
            int next_largest_val_i = first_drop_new_i;

            while (perm[next_largest_val_i] == first_drop_val) {
                next_largest_val_i++;
            }

            int next_largest_val = perm[next_largest_val_i];

            for (int j = next_largest_val_i; j >= first_drop_i + 1; j--) {
                perm[j] = perm[j - 1];
            }

            perm[first_drop_i] = next_largest_val;
            return perm;
        }
    }

    return {};
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"perm"};
    return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                           &NextPermutation, DefaultComparator{}, param_names);
}
