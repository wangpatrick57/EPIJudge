#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "test_framework/generic_test.h"
using namespace std;

string compute_canon_string(const string &word) {
  string canon_string = word;
  sort(canon_string.begin(), canon_string.end());
  return canon_string;
}

vector<vector<string>> FindAnagrams(const vector<string> &dictionary)
{
  unordered_map<string, vector<string>> grouped_words;
  for (const string &word : dictionary) {
    string canon_string = compute_canon_string(word);
    grouped_words[canon_string].push_back(word);
  }

  vector<vector<string>> anagram_groups;
  for (const pair<string, vector<string>> &p : grouped_words) {
    if (p.second.size() > 1) {
      anagram_groups.push_back(p.second);
    }
  }

  return anagram_groups;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
