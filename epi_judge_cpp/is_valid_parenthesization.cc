#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::string;
using namespace std;

vector<char> LEFT_SYMBOLS{'(', '{', '['};
vector<char> RIGHT_SYMBOLS{')', '}', ']'};
map<char, char>LEFT_TO_RIGHT_SYMBOL{
  {'(', ')'},
  {'{', '}'},
  {'[', ']'},
};

bool IsWellFormed(const string &s)
{
  stack<char> open_symbols;

  for (char c : s) {
    if (find(LEFT_SYMBOLS.begin(), LEFT_SYMBOLS.end(), c) != LEFT_SYMBOLS.end()) {
      open_symbols.push(c);
    } else if (find(RIGHT_SYMBOLS.begin(), RIGHT_SYMBOLS.end(), c) != RIGHT_SYMBOLS.end()) {
      if (open_symbols.empty()) {
        return false;
      }

      char top_symbol = open_symbols.top();
      open_symbols.pop();

      if (LEFT_TO_RIGHT_SYMBOL.at(top_symbol) != c) {
        return false;
      }
    } else {
      return false;
    }
  }

  if (!open_symbols.empty()) {
    return false;
  }

  return true;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
