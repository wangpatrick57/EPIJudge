import functools
from typing import List

from test_framework import generic_test
from test_framework.test_failure import TestFailure
from test_framework.test_utils import enable_executor_hook

RED, WHITE, BLUE = range(3)


def dutch_allthreeleft(pivot_index: int, A: List[int]) -> None:
    pivot = A[pivot_index]
    eq_start_i = 0
    gt_start_i = 0

    for i in range(len(A)):
        if A[i] < pivot:
            if eq_start_i == gt_start_i == i:
                pass
            elif eq_start_i == gt_start_i:
                A[eq_start_i], A[i] = A[i], A[eq_start_i]
            elif gt_start_i == i:
                A[eq_start_i], A[i] = A[i], A[eq_start_i]
            else:
                tmp = A[gt_start_i]
                A[gt_start_i] = A[eq_start_i]
                A[eq_start_i] = A[i]
                A[i] = tmp
            eq_start_i += 1
            gt_start_i += 1
        elif A[i] == pivot:
            A[i], A[gt_start_i] = A[gt_start_i], A[i]
            gt_start_i += 1
        else:
            pass


def dutch_onlytwoleft(pivot_index: int, A: List[int]) -> None:
    n = len(A)
    pivot = A[pivot_index]
    eq_start_i = 0
    gt_start_i = n
    unknown_start_i = 0

    while unknown_start_i < gt_start_i:
        if A[unknown_start_i] == pivot:
            unknown_start_i += 1
        elif A[unknown_start_i] < pivot:
            A[eq_start_i], A[unknown_start_i] = A[unknown_start_i], A[eq_start_i]
            eq_start_i += 1
            unknown_start_i += 1
        else:
            gt_start_i -= 1
            A[gt_start_i], A[unknown_start_i] = A[unknown_start_i], A[gt_start_i]
            # don't increment unknown_start_i. we already decremented gt_start_i


def dutch_flag_partition(pivot_index: int, A: List[int]) -> None:
    dutch_onlytwoleft(pivot_index, A)


@enable_executor_hook
def dutch_flag_partition_wrapper(executor, A, pivot_idx):
    count = [0, 0, 0]
    for x in A:
        count[x] += 1
    pivot = A[pivot_idx]

    executor.run(functools.partial(dutch_flag_partition, pivot_idx, A))

    i = 0
    while i < len(A) and A[i] < pivot:
        count[A[i]] -= 1
        i += 1
    while i < len(A) and A[i] == pivot:
        count[A[i]] -= 1
        i += 1
    while i < len(A) and A[i] > pivot:
        count[A[i]] -= 1
        i += 1

    if i != len(A):
        raise TestFailure('Not partitioned after {}th element'.format(i))
    elif any(count):
        raise TestFailure('Some elements are missing from original array')


if __name__ == '__main__':
    exit(
        generic_test.generic_test_main('dutch_national_flag.py',
                                       'dutch_national_flag.tsv',
                                       dutch_flag_partition_wrapper))