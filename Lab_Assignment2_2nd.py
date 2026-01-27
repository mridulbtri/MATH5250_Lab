import time
import random


def generate_list(n):
    L = []
    for _ in range(n):
        L.append(random.randint(1, 100000))
    return L


def test_pop(L):
    start = time.time()
    L.pop()
    end = time.time()
    return end - start


def test_pop_zero(L):
    start = time.time()
    L.pop(0)
    end = time.time()
    return end - start


def test_slice_copy(L):
    start = time.time()
    A = L[:]
    end = time.time()
    return end - start


def test_list_copy(L):
    start = time.time()
    B = list(L)
    end = time.time()
    return end - start


def test_reverse_inplace(L):
    start = time.time()
    L.reverse()
    end = time.time()
    return end - start


def test_reverse_copy(L):
    start = time.time()
    R = L[::-1]
    end = time.time()
    return end - start


def run_tests(N):

    n = N

    for i in range(4):

        print("\nList size:", n)

        L = generate_list(n)

        t1 = test_pop(L.copy())
        t2 = test_pop_zero(L.copy())

        t3 = test_slice_copy(L)
        t4 = test_list_copy(L)

        t5 = test_reverse_inplace(L.copy())
        t6 = test_reverse_copy(L)

        print("pop() time:       ", t1)
        print("pop(0) time:      ", t2)

        print("L[:] time:        ", t3)
        print("list(L) time:     ", t4)

        print("L.reverse() time: ", t5)
        print("L[::-1] time:     ", t6)

        n = n * 2


# Example run
run_tests(10000)
