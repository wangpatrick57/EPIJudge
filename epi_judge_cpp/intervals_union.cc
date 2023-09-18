#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"

using std::cout;
using std::endl;
using std::vector;
using std::sort;

struct Interval {
  struct Endpoint {
    bool is_closed;
    int val;
  };

  Endpoint left, right;
};

vector<Interval> UnionOfIntervals(vector<Interval> intervals) {
  int num_intervals = intervals.size();
  if (num_intervals == 0) {
    return {};
  }

  // sort by begin
  Interval temp = intervals.at(0);
  intervals.at(0) = intervals.at(num_intervals - 1);
  intervals.at(num_intervals - 1) = temp;
  sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
    if (a.left.val == b.left.val) {
      // favors a if both are closed. favors b if both are open
      return a.left.is_closed && !b.left.is_closed;
    }
    return a.left.val < b.left.val;
  });

  // loop through building intervals, knowing that we'll never miss any intervals
  vector<Interval> merged_intervals;
  Interval build_interval = intervals.at(0);
  for (int i = 1; i < num_intervals; i++) {
    const Interval &this_interval = intervals.at(i);

    // see if we can merge this into build
    bool can_add_this;
    if (build_interval.right.val == this_interval.left.val) {
      can_add_this = build_interval.right.is_closed || this_interval.left.is_closed;
    } else {
      can_add_this = build_interval.right.val > this_interval.left.val;
    }

    // if so, merge it. if not, put build in merged and reset build
    if (can_add_this) {
      if (build_interval.right.val == this_interval.right.val) {
        build_interval.right.is_closed = build_interval.right.is_closed || this_interval.right.is_closed;
      } else if (build_interval.right.val < this_interval.right.val) {
        build_interval.right = this_interval.right;
      }
    } else {
      merged_intervals.push_back(build_interval);
      build_interval = this_interval;
    }
  }
  merged_intervals.push_back(build_interval);
  return merged_intervals;
}
struct FlatInterval {
  int left_val;
  bool left_is_closed;
  int right_val;
  bool right_is_closed;

  FlatInterval(int left_val, bool left_is_closed, int right_val,
               bool right_is_closed)
      : left_val(left_val),
        left_is_closed(left_is_closed),
        right_val(right_val),
        right_is_closed(right_is_closed) {}

  explicit FlatInterval(Interval in)
      : left_val(in.left.val),
        left_is_closed(in.left.is_closed),
        right_val(in.right.val),
        right_is_closed(in.right.is_closed) {}

  operator Interval() const {
    return {{left_is_closed, left_val}, {right_is_closed, right_val}};
  }

  bool operator==(const FlatInterval& rhs) const {
    return std::tie(left_val, left_is_closed, right_val, right_is_closed) ==
           std::tie(rhs.left_val, rhs.left_is_closed, rhs.right_val,
                    rhs.right_is_closed);
  }
};

namespace test_framework {
template <>
struct SerializationTrait<FlatInterval>
    : UserSerTrait<FlatInterval, int, bool, int, bool> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const FlatInterval& i) {
  return out << (i.left_is_closed ? '<' : '(') << i.left_val << ", "
             << i.right_val << (i.right_is_closed ? '>' : ')');
}

std::vector<FlatInterval> UnionOfIntervalsWrapper(
    TimedExecutor& executor, const std::vector<FlatInterval>& intervals) {
  std::vector<Interval> casted;
  for (const FlatInterval& i : intervals) {
    casted.push_back(static_cast<Interval>(i));
  }

  std::vector<Interval> result =
      executor.Run([&] { return UnionOfIntervals(casted); });

  return {begin(result), end(result)};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "intervals"};
  return GenericTestMain(args, "intervals_union.cc", "intervals_union.tsv",
                         &UnionOfIntervalsWrapper, DefaultComparator{},
                         param_names);
}
