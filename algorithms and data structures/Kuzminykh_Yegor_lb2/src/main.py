def combine_parts(arr, left, middle, right):

    pointers = [left, middle + 1]
    temp_result = []

    while pointers[0] <= middle and pointers[1] <= right:
        if arr[pointers[0]] ** 2 < arr[pointers[1]] ** 2 or (
                arr[pointers[0]] ** 2 == arr[pointers[1]] ** 2 and arr[pointers[0]] > arr[pointers[1]]):
            temp_result.append(arr[pointers[0]])
            pointers[0] += 1
        else:
            temp_result.append(arr[pointers[1]])
            pointers[1] += 1

    while pointers[0] <= middle:
        temp_result.append(arr[pointers[0]])
        pointers[0] += 1

    while pointers[1] <= right:
        temp_result.append(arr[pointers[1]])
        pointers[1] += 1

    for i, item in enumerate(temp_result):
        arr[left + i] = item


def sorted_insertion(items, start, end):

    for pos in range(start + 1, end + 1):
        key_item = items[pos]
        j = pos - 1
        while j >= start and (
                key_item ** 2 < items[j] ** 2 or (key_item ** 2 == items[j] ** 2 and key_item > items[j])):
            items[j + 1] = items[j]
            j -= 1
        items[j + 1] = key_item


def run_tim_sort(items):

    n = len(items)
    min_run = 32

    for start in range(0, n, min_run):
        end = min(start + min_run - 1, n - 1)
        sorted_insertion(items, start, end)
        print(f"Part {start // min_run}: {' '.join(map(str, items[start:end + 1]))}")

    size = min_run
    while size < n:
        for start in range(0, n, 2 * size):
            mid = min(n - 1, start + size - 1)
            end = min(n - 1, start + 2 * size - 1)

            if mid < end:
                combine_parts(items, start, mid, end)
        size *= 2


if __name__ == '__main__':

    items_amount = int(input())
    items = list(map(int, input().split()))

    run_tim_sort(items)
    print(f"Answer: {' '.join(map(str, items))}")
