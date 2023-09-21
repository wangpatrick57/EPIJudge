#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool isBSTHelper(const unique_ptr<BinaryTreeNode<int>> &tree, int min, int max) {
  if (!tree) {
    return true;
  }
  if (tree->data < min || tree->data > max) {
    return false;
  }
  return isBSTHelper(tree->left, min, tree->data) && isBSTHelper(tree->right, tree->data, max);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>> &tree)
{
  return isBSTHelper(tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
