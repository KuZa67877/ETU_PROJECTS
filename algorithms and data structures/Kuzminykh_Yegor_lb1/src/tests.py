from main import unrolled_linked_list
from main import Node


def check(arr1, arr2):
    my_unrolled_list = unrolled_linked_list()
    for i in range(len(arr1)):
        my_unrolled_list.append(arr1[i])
        print(my_unrolled_list.print_info())
    for i in range(len(arr2)):
        my_unrolled_list.delete(arr2[i])
        print(my_unrolled_list.print_info())

    assert (my_unrolled_list.all_length == 0)


def test_assert(value=100):
    my_unrolled_list = unrolled_linked_list()
    for i in range(10):
        my_unrolled_list.insert(value, i)
    assert (my_unrolled_list.all_length == 10)


def test_search(len=10):
    my_unrolled_list = unrolled_linked_list()
    for i in range(len):
        my_unrolled_list.append(i)
    array = []
    for i in range(my_unrolled_list.all_length):
        array.append(my_unrolled_list.search_by_index(i))
    assert array == [x for x in range(len)]


def test_print():
    my_unrolled_list = unrolled_linked_list()
    for i in range(10):
        my_unrolled_list.append(i)
    assert my_unrolled_list.print_info() == '0 1 2 3 4 5 6 7 8 9 '
