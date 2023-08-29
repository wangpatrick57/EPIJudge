#include "list_node.h"
#include "test_framework/generic_test.h"
#include <memory>

using namespace std;

shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>> &L)
{
    shared_ptr<ListNode<int>> it = L;
    shared_ptr<ListNode<int>> even_tail;
    shared_ptr<ListNode<int>> odd_tail;
    shared_ptr<ListNode<int>> odd_head;
    int n = 0;

    while (it != nullptr) {
        if (n == 0) {
            even_tail = it;
        } else if (n == 1) {
            odd_head = it;
            odd_tail = it;
        } else if (n % 2 == 0) {
            even_tail->next = it;
            even_tail = it;
        } else {
            odd_tail->next = it;
            odd_tail = it;
        }

        it = it->next;
        n++;
    }

    if (even_tail != nullptr && odd_head != nullptr) {
        even_tail->next = odd_head;
    }

    if (odd_tail != nullptr) {
        odd_tail->next = nullptr;
    }

    return L;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L"};
    return GenericTestMain(args, "even_odd_list_merge.cc",
                           "even_odd_list_merge.tsv", &EvenOddMerge,
                           DefaultComparator{}, param_names);
}
