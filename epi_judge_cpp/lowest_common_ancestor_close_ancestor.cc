#include <memory>
#include <unordered_set>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using namespace std;

BinaryTreeNode<int> *Lca(const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1)
{
  unordered_set<BinaryTreeNode<int> *> visited_nodes;
  BinaryTreeNode<int> *it0 = node0.get();
  BinaryTreeNode<int> *it1 = node1.get();
  while (it0 || it1) {
    // insert itx itself before first itx = itx->parent call in case the nodes are equal
    if (it0) {
      if (visited_nodes.emplace(it0).second == false) {
        return it0;
      }
      it0 = it0->parent;
    }
    if (it1) {
      if (visited_nodes.emplace(it1).second == false) {
        return it1;
      }
      it1 = it1->parent;
    }
  }
  throw invalid_argument("node0 and node1 are not in the same tree");
}
int LcaWrapper(TimedExecutor &executor,
               const unique_ptr<BinaryTreeNode<int>> &tree, int key0,
               int key1)
{
  const unique_ptr<BinaryTreeNode<int>> &node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>> &node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&]
                             { return Lca(node0, node1); });

  if (!result)
  {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
