from typing import List

from test_framework import generic_test


def search_first_of_k(A: List[int], k: int) -> int:
    l = 0
    r = len(A)

    while l < r:
        m = l + (r - l) // 2

        if A[m] == k:
            if m == 0 or A[m - 1] != k:
                return m
            else:
                r = m
        elif A[m] < k:
            l = m + 1
        else:
            r = m

    return -1


if __name__ == '__main__':
    exit(
        generic_test.generic_test_main('search_first_key.py',
                                       'search_first_key.tsv',
                                       search_first_of_k))
