#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using namespace std;

const vector<vector<char>> DIGIT_MAPPING = {
    {'0'},
    {'1'},
    {'A', 'B', 'C'},
    {'D', 'E', 'F'},
    {'G', 'H', 'I'},
    {'J', 'K', 'L'},
    {'M', 'N', 'O'},
    {'P', 'Q', 'R', 'S'},
    {'T', 'U', 'V'},
    {'W', 'X', 'Y', 'Z'},
};

vector<string> PhoneMnemonic(const string &phone_number)
{
    int n = phone_number.size();
    vector<string> mnemonics;
    vector<int> letter_i_per_num(n, 0);
    vector<int> phone_number_digits;

    for (int i = 0; i < n; i++) {
        int digit = phone_number[i] - '0';
        phone_number_digits.push_back(digit);
    }

    while (true) {
        // build
        vector<char> mutable_mnemonic;
        for (int i = 0; i < n; i++) {
            int digit = phone_number_digits[i];
            mutable_mnemonic.push_back(DIGIT_MAPPING[digit][letter_i_per_num[i]]);
        }
        string mnemonic(mutable_mnemonic.begin(), mutable_mnemonic.end());
        mnemonics.push_back(mnemonic);

        // increment letter_i_per_num
        int i;
        for (i = n - 1; i >= 0; i--) {
            letter_i_per_num[i]++;
            int digit = phone_number_digits[i];
            if (letter_i_per_num[i] == DIGIT_MAPPING[digit].size()) {
                letter_i_per_num[i] = 0;
            } else {
                break;
            }
        }
        // i == -1 means we didn't break
        if (i == -1) {
            break;
        }
    }

    return mnemonics;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"phone_number"};
    return GenericTestMain(args, "phone_number_mnemonic.cc",
                           "phone_number_mnemonic.tsv", &PhoneMnemonic,
                           UnorderedComparator{}, param_names);
}
