from test_framework import generic_test

parity_cache = dict()

def parity_8bit(x: int) -> int:
    parity = 0
    for _ in range(8):
        parity ^= x & 1
        x >>= 1
    return parity

def parity(x: int) -> int:
    global parity_cache
    parity = 0
    for _ in range(8):
        x_8bit = x & 0xFF
        if x_8bit not in parity_cache:
            parity_cache[x_8bit] = parity_8bit(x_8bit)
        x_8bit_parity = parity_cache[x_8bit]
        parity ^= x_8bit_parity
        x >>= 8
    return parity


if __name__ == '__main__':
    exit(generic_test.generic_test_main('parity.py', 'parity.tsv', parity))
