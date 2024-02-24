from typing import List

from test_framework import generic_test


def buy_and_sell_stock_once(prices: List[float]) -> float:
    n = len(prices)
    max_profit = 0
    lowest_price_before_i = prices[0]

    for i in range(1, n):
        max_profit_selling_i = prices[i] - lowest_price_before_i
        max_profit = max(max_profit, max_profit_selling_i)
        lowest_price_before_i = min(lowest_price_before_i, prices[i])

    return max_profit


if __name__ == '__main__':
    exit(
        generic_test.generic_test_main('buy_and_sell_stock.py',
                                       'buy_and_sell_stock.tsv',
                                       buy_and_sell_stock_once))
