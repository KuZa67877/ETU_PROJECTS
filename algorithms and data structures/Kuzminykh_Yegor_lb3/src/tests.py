import random

from main import delete_node, insert, in_order


def test_new_tree():
    val = random.randint(1, 100)
    my_tree = insert(val, None)

    result = [val]
    my_answer = in_order(my_tree)
    assert result == my_answer, f'Error: {result} ≠ {my_answer}'

def test_insert():
    my_tree = None
    insert_values = random.sample(range(1, 100), 6)  # generate 6 unique random numbers
    for v in insert_values:
        my_tree = insert(v, my_tree)

    my_answer = in_order(my_tree)
    result = sorted(insert_values)
    assert result == my_answer, f'Error: {result} ≠ {my_answer}'

def test_remove_min():
    my_tree = None
    insert_values = random.sample(range(1, 100), 6)
    for v in insert_values:
        my_tree = insert(v, my_tree)

    my_tree = delete_node(min(insert_values), my_tree)
    my_answer = in_order(my_tree)
    result = sorted(insert_values)[1:]  # exclude min value
    assert result == my_answer, f'Error: {result} ≠ {my_answer}'

def test_remove_max():
    my_tree = None
    insert_values = random.sample(range(1, 100), 6)
    for v in insert_values:
        my_tree = insert(v, my_tree)

    my_tree = delete_node(max(insert_values), my_tree)
    my_answer = in_order(my_tree)
    result = sorted(insert_values)[:-1]
    assert result == my_answer, f'Error: {result} ≠ {my_answer}'

def test_remove_some_node():
    my_tree = None
    insert_values = random.sample(range(1, 100), 6)
    for v in insert_values:
        my_tree = insert(v, my_tree)

    remove_values = random.sample(insert_values, 2)
    for v in remove_values:
        my_tree = delete_node(v, my_tree)

    my_answer = in_order(my_tree)
    result = sorted(list(set(insert_values) - set(remove_values)))
    assert result == my_answer, f'Error: {result} ≠ {my_answer}'
