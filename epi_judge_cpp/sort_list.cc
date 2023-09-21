#include <memory>
#include <iostream>

#include "list_node.h"
#include "test_framework/generic_test.h"

using std::cout;
using std::endl;

shared_ptr<ListNode<int>> merge_lists(shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>();
  shared_ptr<ListNode<int>> build_tail = dummy_head;

  while (L1 && L2) {
    if (L1->data < L2->data) {
      build_tail->next = L1;
      build_tail = build_tail->next;
      L1 = L1->next;
    } else {
      build_tail->next = L2;
      build_tail = build_tail->next;
      L2 = L2->next;
    }
  }
  if (L1 && !L2) {
    build_tail->next = L1;
  } else if (L2 && !L1) {
    build_tail->next = L2;
  }

  return dummy_head->next;
}

shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L)
{
  if (!L) {
    return nullptr;
  } else if (!L->next) {
    return L; // can't break this list in half without infinite recursion
  } else {
    // find tail of left list ((n + 1) / 2)
    shared_ptr<ListNode<int>> slow = L, fast = L->next;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    shared_ptr<ListNode<int>> left_tail = slow;

    // recurse and merge
    shared_ptr<ListNode<int>> left_head = L;
    shared_ptr<ListNode<int>> right_head = left_tail->next;
    left_tail->next = nullptr;
    return merge_lists(StableSortList(left_head), StableSortList(right_head));
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
