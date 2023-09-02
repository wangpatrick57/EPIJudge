#include <vector>
#include <stack>
#include <utility>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using namespace std;

void PreorderTraversalRecursive(const unique_ptr<BinaryTreeNode<int>> &node, vector<int> &traversal)
{
  if (node == nullptr) {
    return;
  }

  traversal.push_back(node->data);
  PreorderTraversalRecursive(node->left, traversal);
  PreorderTraversalRecursive(node->right, traversal);
}

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree)
{
  vector<int> traversal;
  PreorderTraversalRecursive(tree, traversal);
  return traversal;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
