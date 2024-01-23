class Node:
    def __init__(self):
        self.length = 0
        self.array = [0] * self.length
        self.next = None


class unrolled_linked_list:

    def __init__(self, n_array=4):
        self.n_array = n_array
        self.head = None
        self.tail = None
        self.all_length = 0

    def insert(self, value, index):
        if index < 0 or index > self.all_length:
            return

        if self.all_length == 0 or self.all_length <= index:
            self.append(value)
        else:
            global_index = 0
            my_temp = self.head
            prev_temp = None
            while my_temp is not None:
                for i in range(len(my_temp.array)):
                    if global_index == index:
                        if my_temp.length + 1 <= self.n_array:
                            my_temp.array.insert(i, value)
                        else:
                            new_node = Node()
                            split_index = self.n_array // 2
                            new_node.array = my_temp.array[split_index:]
                            my_temp.array = my_temp.array[:split_index]

                            if prev_temp is None:
                                self.head = new_node
                            else:
                                prev_temp.next = new_node
                            new_node.next = my_temp.next

                            if i < split_index:
                                my_temp.array.insert(i, value)
                            else:
                                new_node.array.insert(i - split_index, value)
                        self.all_length += 1
                        return
                    global_index += 1
                prev_temp = my_temp
                my_temp = my_temp.next

    def append(self, value):
        if self.head == None:
            self.head = Node()
            self.head.array.append(value)
            self.head.length += 1
            self.all_length += 1
            self.tail = self.head

        elif self.tail.length + 1 <= self.n_array:
            self.tail.array.append(value)
            self.tail.length += 1
            self.all_length += 1
        else:
            new_node = Node()
            half_length = self.tail.length // 2
            mini_array = self.tail.array[-half_length:]
            new_node.array.extend(mini_array)
            self.tail.array = self.tail.array[:-half_length]

            new_node.array.append(value)
            new_node.length = len(new_node.array)
            self.all_length += 1
            self.tail.length = half_length
            self.tail.next = new_node
            self.tail = new_node

    def print_info(self):
        temp = self.head
        result_string = ''
        while temp != None:
            for i in range(len(temp.array)):
                result_string += f'{temp.array[i]} '
            temp = temp.next
        return result_string

    def delete(self, value):
        temp = self.head
        prev_temp = None
        while temp is not None:
            i = 0
            while i < len(temp.array):
                if temp.array[i] == value:
                    temp.array.pop(i)
                    temp.length -= 1
                else:
                    i += 1

            if len(temp.array) < self.n_array // 2:
                if prev_temp is not None and len(prev_temp.array) + len(temp.array) <= self.n_array:
                    prev_temp.array.extend(temp.array)
                    prev_temp.next = temp.next
                    temp = prev_temp
                elif temp.next is not None and len(temp.array) + len(temp.next.array) <= self.n_array:
                    temp.array.extend(temp.next.array)
                    temp.next = temp.next.next

            prev_temp = temp
            temp = temp.next

        if self.head is not None and len(self.head.array) == 0:
            self.head = self.head.next

        self.all_length -= 1

    def delete_by_index(self, index):
        if index < 0 or index >= self.all_length:
            return
        temp = self.head
        prev_temp = None
        global_index = 0

        while temp is not None:
            i = 0
            while i < len(temp.array):
                if global_index == index:

                    temp.array.pop(i)
                    temp.length -= 1

                    if len(temp.array) < self.n_array // 2:
                        if prev_temp is not None and len(prev_temp.array) + len(temp.array) <= self.n_array:
                            prev_temp.array.extend(temp.array)
                            prev_temp.next = temp.next
                        elif temp.next is not None and len(temp.array) + len(temp.next.array) <= self.n_array:
                            temp.array.extend(temp.next.array)
                            temp.next = temp.next.next

                    self.all_length -= 1
                    return

                i += 1
                global_index += 1

            prev_temp = temp
            temp = temp.next

        if self.head is not None and len(self.head.array) == 0:
            self.head = self.head.next

    def search(self, value):
        temp = self.head
        while temp.next != None:
            for i in range(len(temp.array)):
                if value == temp.array[i]:
                    return temp.array[i]
            temp = temp.next

    def search_by_index(self, index):
        global_index = 0
        temp = self.head
        while temp != None:
            for i in range(len(temp.array)):
                if global_index == index:
                    return temp.array[i]
                global_index += 1
            temp = temp.next
