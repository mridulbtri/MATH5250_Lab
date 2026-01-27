import time
import random


def generate_list(n):
    L = []
    for i in range(n):
        L.append(random.randint(1, 100000))
    return L


def test_pop(L): # removes the last element from the list

    start = time.time()
    for i in range(len(L)):
        L.pop()
    end = time.time()
    return end - start


def test_pop_zero(L): #removes the first element from the list
    start = time.time()
    for i in range(len(L)):
        L.pop(0)
    end = time.time()
    return end - start


def test_slice_copy(L): #creates the shallow copy of the list
    start = time.time()
    A = L[:]
    end = time.time()
    return end - start


def test_list_copy(L): 
    start = time.time()
    B = list(L)
    end = time.time()
    return end - start


def test_reverse_inplace(L): #modifies the list in place
    start = time.time()
    L.reverse()
    end = time.time()
    return end - start


def test_reverse_copy(L): #creates new reversed copy
    start = time.time()
    R = L[::-1]
    end = time.time()
    return end - start


def run_tests(N):

    n = N

    for i in range(4):

        L = generate_list(n)

        t1 = test_pop(L.copy()) # Passing L.copy() because we don't want to change L during operations performed inside above functions
        t2 = test_pop_zero(L.copy())

        t3 = test_slice_copy(L.copy())
        t4 = test_list_copy(L.copy())

        t5 = test_reverse_inplace(L.copy())
        t6 = test_reverse_copy(L.copy())

        print("\n================================================\n")
        print("List size:", n)

        print("pop() time:       ", t1)
        print("pop(0) time:      ", t2)

        print("L[:] time:        ", t3)
        print("list(L) time:     ", t4)

        print("L.reverse() time: ", t5)
        print("L[::-1] time:     ", t6)
        print("\n")

        n = n * 2


# Example run
run_tests(10000)
