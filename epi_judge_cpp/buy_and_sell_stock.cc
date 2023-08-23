#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using namespace std;
double BuyAndSellStockOnce(const vector<double> &prices)
{
    int n = prices.size();

    if (n == 0) {
        return 0;
    }

    double lowest_so_far = prices[0];
    double max_profit = 0;

    for (int i = 1; i < n; i++) {
        max_profit = max(max_profit, prices[i] - lowest_so_far);
        lowest_so_far = min(lowest_so_far, prices[i]);
    }
    
    return max_profit;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"prices"};
    return GenericTestMain(args, "buy_and_sell_stock.cc",
                           "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                           DefaultComparator{}, param_names);
}
