class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def calculate_height(root):
    if root is None:
        return 0
    return 1 + max(calculate_height(root.left), calculate_height(root.right))


def check(root):
    if root is None:
        return True
    conditions = [
        abs(calculate_height(root.left) - calculate_height(root.right)) <= 1,
        check(root.left),
        check(root.right)
    ]
    return all(conditions)


def calculate_diff(current_root, min_diff):
    if current_root.left is not None:
        min_diff = min(min_diff, abs(current_root.val - current_root.left.val))
        min_diff = calculate_diff(current_root.left, min_diff)

    if current_root.right is not None:
        min_diff = min(min_diff, abs(current_root.val - current_root.right.val))
        min_diff = calculate_diff(current_root.right, min_diff)

    return min_diff


def diff(root):
    if root is None:
        return float('inf')
    else:
        return calculate_diff(root, float('inf'))


def refresh_height(root):
    root.height = calculate_height(root)
    return root


def imbalance_factor(root):
    left_height = calculate_height(root.left)
    right_height = calculate_height(root.right)
    return right_height - left_height


def rotate_anti_clockwise(root):
    temp = root.left
    root.left = temp.right
    temp.right = refresh_height(root)
    return refresh_height(temp)


def rotate_clockwise(root):
    pivot = root.right
    root.right = pivot.left
    pivot.left = refresh_height(root)
    return refresh_height(pivot)


def balance_tree(root):
    root = refresh_height(root)
    if imbalance_factor(root) == 2:
        if imbalance_factor(root.right) < 0:
            root.right = rotate_anti_clockwise(root.right)
        return rotate_clockwise(root)
    if imbalance_factor(root) == -2:
        if imbalance_factor(root.left) > 0:
            root.left = rotate_clockwise(root.left)
        return rotate_anti_clockwise(root)

    return root


def insert(value, root):
    if root is None:
        return Node(value)

    if value < root.val:
        root.left = insert(value, root.left)
    else:
        root.right = insert(value, root.right)
    return balance_tree(root)


def seek_minimum(root):
    if root.left is None:
        return root
    else:
        return seek_minimum(root.left)

def extract_minimum(root):
    if root.left is None:
        return root.right
    root.left = extract_minimum(root.left)
    return balance_tree(root)

def delete_node(value, root): # удаление узла
    if root is None:
        return 0
    if value < root.val:
        root.left = delete_node(value, root.left)
    elif value > root.val:
        root.right = delete_node(value, root.right)
    else: # value = node.val
        temp_left = root.left
        temp_right = root.right
        if temp_right is None:
            return temp_left
        smallest_node = seek_minimum(temp_right)
        smallest_node.right = extract_minimum(temp_right)
        smallest_node.left = temp_left
        return balance_tree(smallest_node)
    return balance_tree(root)

def in_order(root: Node):
    if root is None:
        return []
    return [*in_order(root.left), root.val, *in_order(root.right)]

