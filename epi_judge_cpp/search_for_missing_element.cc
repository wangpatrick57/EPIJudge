#include <vector>
#include <numeric>
#include <functional>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"

using namespace std;

struct DuplicateAndMissing
{
  int duplicate, missing;
};

DuplicateAndMissing FindDuplicateMissing(const vector<int> &A)
{
  // sum(A) - sum([0, n-1]) = -m + d
  // xor(A) ^ xor([0, n-1]) = m ^ d
  int n = A.size();

  // xor(A) ^ xor([0, n-1]) will give a non-zero number with 1s at all differing bits
  int xor_sum = reduce(A.begin(), A.end(), 0, bit_xor<int>());
  for (int i = 0; i <= n - 1; i++) {
    xor_sum ^= i;
  }

  // the numbers in [0, n-1] with any differing bit will contain either the duplicate or the missing, but not both
  int one_differing_bit = xor_sum & ~(xor_sum - 1);
  int dup_or_miss = 0;
  for (auto elem : A) {
    if (elem & one_differing_bit) {
      dup_or_miss ^= elem;
    }
  }
  for (int i = 0; i <= n - 1; i++) {
    if (i & one_differing_bit) {
      dup_or_miss ^= i;
    }
  }

  // figure out if it's the duplicate (easier than figuring out if it's the missing)
  bool is_dup = false;
  for (auto elem : A) {
    if (elem == dup_or_miss) {
      is_dup = true;
      break;
    }
  }
    
  // handle both cases
  int a_add_sum = reduce(A.begin(), A.end());
  int n_add_sum = (n - 1 + 1) * (n - 1) / 2;
  int dup, miss;
  if (is_dup) {
    dup = dup_or_miss;
    miss = dup - (a_add_sum - n_add_sum);
  } else {
    miss = dup_or_miss;
    dup = a_add_sum - n_add_sum + miss;
  }

  return {dup, miss};
}

namespace test_framework
{
  template <>
  struct SerializationTrait<DuplicateAndMissing>
      : UserSerTrait<DuplicateAndMissing, int, int>
  {
  };
} // namespace test_framework

bool operator==(const DuplicateAndMissing &lhs,
                const DuplicateAndMissing &rhs)
{
  return std::tie(lhs.duplicate, lhs.missing) ==
         std::tie(rhs.duplicate, rhs.missing);
}

std::ostream &operator<<(std::ostream &out, const DuplicateAndMissing &x)
{
  return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "search_for_missing_element.cc", "find_missing_and_duplicate.tsv",
      &FindDuplicateMissing, DefaultComparator{}, param_names);
}
