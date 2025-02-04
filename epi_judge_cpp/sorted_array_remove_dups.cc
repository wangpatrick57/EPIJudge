#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int> *A_ptr)
{
    vector<int> &A = *A_ptr;
    int n = A.size();
    int first_invalid_i = 0;

    for (int i = 0; i < n; i++) {
        if (first_invalid_i == 0 || A[first_invalid_i - 1] != A[i]) {
            A[first_invalid_i++] = A[i];
        }
    }
    return first_invalid_i;
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor &executor, vector<int> A)
{
    int end = executor.Run([&]
                           { return DeleteDuplicates(&A); });
    A.resize(end);
    return A;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "A"};
    return GenericTestMain(
        args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
        &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
