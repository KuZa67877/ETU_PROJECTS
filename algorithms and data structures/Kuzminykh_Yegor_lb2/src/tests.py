import random
from main import run_tim_sort

def test_from_moevm():
    array = [-4, 7, 5, 3, 5, -4, 2, -1, -9, -8, -3, 0, 9, -7, -4, -10, -4, 2, 6, 1, -2, -3, -1, -8, 0, -8, -7, -3, 5, -1, -8, -8, 8, -1, -3, 3, 6, 1, -8, -1, 3, -9, 9, -6]
    run_tim_sort(array)
    assert array == [0, 0, 1, 1, -1, -1, -1, -1, -1, 2, 2, -2, 3, 3, 3, -3, -3, -3, -3, -4, -4, -4, -4, 5, 5, 5, 6, 6, -6, 7, -7, -7, 8, -8, -8, -8, -8, -8, -8, 9, 9, -9, -9, -10]

def test_short_array():
    array = [0,-1,1]
    run_tim_sort(array)
    assert array==[0,1,-1]

def test_len(x = 1000):
    array = []
    for i in range(x):
        array.append(random.randint(-100,100))

    run_tim_sort(array)

    assert len(array) == x