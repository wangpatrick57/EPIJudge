#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::stack;
using std::cout;
using std::endl;

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int> &preorder_sequence)
{
  stack<int> next_highest_value;
  unique_ptr<BstNode<int>> dummy_root = std::make_unique<BstNode<int>>(0);
  stack<BstNode<int> *> parents;
  BstNode<int> *curr_node = dummy_root.get();
  for (int val : preorder_sequence) {
    // invariant 1.1: the top of next_highest_value will hold the next highest value in an inorder traversal of the current tree
    // invariant 1.2: the top of next_highest_value will be the value of the closest ancestor node with an empty right child
    // invariant 2.1: parents will hold the path of curr_node's parents until the root (not the dummy root), including curr_node itself
    // invariant 2.2: parents will be empty if curr_node is the dummy root
    // in each loop, we create a new node with the val and need to decide where to place it. this node will become the next "curr_node"
    unique_ptr<BstNode<int>> new_node = std::make_unique<BstNode<int>>(val);
    if (next_highest_value.size() == 0 || val < next_highest_value.top()) {
      // case: place new_node to the left of curr_node
      curr_node->left = std::move(new_node);
      curr_node = curr_node->left.get(); // we need to do this since curr_node->left owns new_node now
    } else {
      // case: place new_node to the right of some node in parents (possibly curr_node)
      // if we pop until next_highest_value.size() == 0, that simply means the next highest value is +inf
      int last_popped_val;
      assert(next_highest_value.size() > 0); // so that last_popped_val is set to something
      while (next_highest_value.size() > 0 && val > next_highest_value.top()) {
        last_popped_val = next_highest_value.top();
        next_highest_value.pop();
      }
      // the most recently popped val is the largest one that is < val. new_node should thus be the right child of the node with that popped val
      while (parents.top()->data != last_popped_val) {
        parents.pop();
        assert(!parents.empty());
      }
      parents.top()->right = std::move(new_node);
      curr_node = parents.top()->right.get(); // we need to use parents.top() instead of new_node since parents.top()->right owns new_node now
    }
    // by this point, curr_node has been set to the node with value val (new_node)
    assert(curr_node->data == val);
    parents.push(curr_node);
    // since we just pushed curr_node we also push val
    next_highest_value.push(val);
  }
  return std::move(dummy_root->left);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
