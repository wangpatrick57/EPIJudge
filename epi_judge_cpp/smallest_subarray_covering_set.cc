#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using namespace std;

struct Subarray
{
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords)
{
  int num_keywords = keywords.size();
  if (num_keywords == 0) {
    return {0, 0};
  }

  unordered_map<string, int> keyword_count;
  int best_interval_length = paragraph.size() + 1;
  Subarray best_interval = {-1, -1};
  int l = 0, r = 0;
  while (r < paragraph.size()) {
    // move r to barely cover all keywords
    while (keyword_count.size() < num_keywords) {
      const string &word = paragraph.at(r);
      if (keywords.count(word) != 0) {
        keyword_count[word]++;
      }
      r++;
      // special case: moved off the end but still haven't covered all keywords
      if (r == paragraph.size()) {
        break;
      }
    }
    // invariant: r will be at the index after the one that caused all keywords to be contained

    // move l to barely lose keywords
    while (keyword_count.size() == num_keywords) {
      const string &word = paragraph.at(l);
      if (keywords.count(word) != 0) {
        keyword_count[word]--;
        // assert(keyword_count[word] >= 0);
        if (keyword_count[word] == 0) {
          // erase so that keyword_count.size() counts how many keywords are present
          keyword_count.erase(word);
        }
      }
      l++;
    }
    // invariant: l will be at the index after the one that caused not all keywords to be contained

    // check local best interval against current best
    int start = l - 1;
    int end = r - 1; // assuming inclusive
    int interval_length = end - start + 1;
    if (interval_length < best_interval_length) {
      best_interval_length = interval_length;
      best_interval = {start, end};
    }
  }
  return best_interval;
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords)
{
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&]
      { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end)
  {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++)
  {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty())
  {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
