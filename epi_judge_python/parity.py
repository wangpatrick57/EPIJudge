from test_framework import generic_test

parity_cache = dict()

def parity_base(x: int) -> int:
    parity = 0
    while x:
        parity ^= 1
        x = x & x - 1
    return parity

def parity(x: int) -> int:
    global parity_cache
    parity = 0
    for _ in range(4):
        x_16bit = x & 0xFFFF
        if x_16bit not in parity_cache:
            parity_cache[x_16bit] = parity_base(x_16bit)
        x_16bit_parity = parity_cache[x_16bit]
        parity ^= x_16bit_parity
        x >>= 16
    return parity


if __name__ == '__main__':
    exit(generic_test.generic_test_main('parity.py', 'parity.tsv', parity))
