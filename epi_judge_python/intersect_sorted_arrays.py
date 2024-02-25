from typing import List

from test_framework import generic_test


def intersect_two_sorted_arrays(A: List[int], B: List[int]) -> List[int]:
    intersection = []
    An = len(A)
    Bn = len(B)
    Ai = 0
    Bi = 0

    while Ai < An and Bi < Bn:
        if A[Ai] == B[Bi]:
            if len(intersection) == 0 or intersection[-1] != A[Ai]:
                intersection.append(A[Ai])
            Ai += 1
            Bi += 1
        elif A[Ai] < B[Bi]:
            Ai += 1
        else:
            Bi += 1

    return intersection


if __name__ == '__main__':
    exit(
        generic_test.generic_test_main('intersect_sorted_arrays.py',
                                       'intersect_sorted_arrays.tsv',
                                       intersect_two_sorted_arrays))
