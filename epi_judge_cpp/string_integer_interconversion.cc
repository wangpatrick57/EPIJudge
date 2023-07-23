#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x)
{
    string res;
    bool is_negative = x < 0;

    // cannot convert x to positive in case x is int min

    do {
        res.push_back('0' + abs(x % 10));
        x /= 10;
    } while (x);

    if (is_negative) {
        res.push_back('-');
    }
    
    return {res.rbegin(), res.rend()};
}
int StringToInt(const string &s)
{
    int res = 0;

    int sign = s[0] == '-' ? -1 : 1;

    for (char c : s) {
        if (c == '+' || c == '-') {
            continue;
        }

        res *= 10;
        res += c - '0';
    }

    return sign * res;
}
void Wrapper(int x, const string &s)
{
    if (stoi(IntToString(x)) != x)
    {
        throw TestFailure("Int to string conversion failed");
    }

    if (StringToInt(s) != x)
    {
        throw TestFailure("String to int conversion failed");
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "s"};
    return GenericTestMain(args, "string_integer_interconversion.cc",
                           "string_integer_interconversion.tsv", &Wrapper,
                           DefaultComparator{}, param_names);
}
