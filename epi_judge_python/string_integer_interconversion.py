from test_framework import generic_test
from test_framework.test_failure import TestFailure


def int_to_string(x: int) -> str:
    sign = '' if x >= 0 else '-'
    x = abs(x)
    num_str = ''

    while x:
        num_str += chr(x % 10 + 48)
        x //= 10

    num_str = ''.join(reversed(num_str))
    num_str = '0' if num_str == '' else num_str
    return sign + num_str


def string_to_int(s: str) -> int:
    n = len(s)
    sign = 1
    i = 0
    num = 0
    if s[i] == '+':
        i += 1
    elif s[i] == '-':
        sign = -1
        i += 1

    while i < n:
        num *= 10
        num += ord(s[i]) - 48
        i += 1

    return sign * num


def wrapper(x, s):
    if int(int_to_string(x)) != x:
        raise TestFailure('Int to string conversion failed')
    if string_to_int(s) != x:
        raise TestFailure('String to int conversion failed')


if __name__ == '__main__':
    exit(
        generic_test.generic_test_main('string_integer_interconversion.py',
                                       'string_integer_interconversion.tsv',
                                       wrapper))
