#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using namespace std;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator &sequence_end)
{
  priority_queue<int, vector<int>, function<bool(int, int)>> left_heap([](int a, int b)
                                                                       { return a <= b; });
  priority_queue<int, vector<int>, function<bool(int, int)>> right_heap([](int a, int b)
                                                                        { return a >= b; });
  vector<double> medians;
  bool has_middle_val = false;
  int middle_val;

  for (vector<int>::const_iterator it = sequence_begin; it != sequence_end; it++) {
    // push *it into a heap or into the middle
    if (!has_middle_val) {
      if (left_heap.size() == 0 && right_heap.size() == 0) {
        middle_val = *it;
      } else {
        assert(left_heap.size() > 0 && right_heap.size() > 0);
        if (*it < left_heap.top()) {
          middle_val = left_heap.top();
          left_heap.pop();
          left_heap.push(*it);
        } else if (*it > right_heap.top()) {
          middle_val = right_heap.top();
          right_heap.pop();
          right_heap.push(*it);
        } else {
          middle_val = *it;
        }
      }
      has_middle_val = true;
    } else {
      if (*it <= middle_val) {
        left_heap.push(*it);
        right_heap.push(middle_val);
      } else {
        left_heap.push(middle_val);
        right_heap.push(*it);
      }
      has_middle_val = false;
    }

    // compute the median
    double median = has_middle_val ? middle_val : (double)(left_heap.top() + right_heap.top()) / 2;
    medians.push_back(median);
  }

  return medians;
}
vector<double> OnlineMedianWrapper(const vector<int> &sequence)
{
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
