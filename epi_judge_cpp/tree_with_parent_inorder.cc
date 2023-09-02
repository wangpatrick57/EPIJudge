#include <vector>
#include <memory>
#include <assert.h>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using namespace std;

// TODO: rewrite this to not have null be the base case

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree)
{
  vector<int> traversal;
  BinaryTreeNode<int> *node = tree.get();

  if (node == nullptr) {
    return traversal;
  }

  BinaryTreeNode<int> *old_node = nullptr;

  while (true) {
    int next_node_index;
    BinaryTreeNode<int> *next_nodes[] = {node->left.get(), node->right.get(), node->parent};

    if (old_node == node->parent) {
      next_node_index = 0;
    } else if (old_node == node->left.get()) {
      next_node_index = 1;
      // whenever next_node_index gets set to 1, we push into traversal
      traversal.push_back(node->data);
    } else if (old_node == node->right.get()) {
      next_node_index = 2;
    } else {
      assert(false);
    }

    while (next_node_index < 2 && next_nodes[next_node_index] == nullptr) {
      next_node_index++;

      // whenever next_node_index gets set to 1, we push into traversal
      if (next_node_index == 1) {
        traversal.push_back(node->data);
      }
    }

    BinaryTreeNode<int> *next_node = next_nodes[next_node_index];

    if (next_node == nullptr) {
      assert(next_node_index == 2);
      return traversal;
    }

    old_node = node;
    node = next_node;
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
