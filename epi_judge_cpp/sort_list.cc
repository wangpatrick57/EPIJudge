#include <memory>
#include <iostream>

#include "list_node.h"
#include "test_framework/generic_test.h"

using std::cout;
using std::endl;

shared_ptr<ListNode<int>> merge_lists(shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
  if (!L1 && !L2) {
    return nullptr;
  } else if (!L1) {
    return L2;
  } else if (!L2) {
    return L1;
  }

  shared_ptr<ListNode<int>> head;
  shared_ptr<ListNode<int>> build_tail;

  while (L1 && L2) {
    if (L1->data < L2->data) {
      if (build_tail) {
        build_tail->next = L1;
      }
      build_tail = L1;
      L1 = L1->next;
    } else {
      if (build_tail) {
        build_tail->next = L2;
      }
      build_tail = L2;
      L2 = L2->next;
    }
    if (!head) {
      head = build_tail;
    }
  }

  if (L1) {
    build_tail->next = L1;
  } else {
    build_tail->next = L2;
  }
  if (!head) {
    head = build_tail;
  }

  return head;
}

shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L)
{
  if (!L) {
    return nullptr;
  } else {
    // find tail of left list ((n + 1) / 2)
    shared_ptr<ListNode<int>> slow = L, fast = L->next;
    if (fast) {
      fast = fast->next;
    }
    while (fast) {
      slow = slow->next;
      fast = fast->next;
      if (fast) {
        fast = fast->next;
      }
    }
    shared_ptr<ListNode<int>> left_tail = slow;

    // recurse
    shared_ptr<ListNode<int>> left_head = L;
    shared_ptr<ListNode<int>> right_head = left_tail->next;
    left_tail->next = nullptr;
    // this if condition avoids infinite recursion
    if (left_head && right_head) {
      left_head = StableSortList(left_head);
      right_head = StableSortList(right_head);
    }

    // merge
    return merge_lists(left_head, right_head);
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
