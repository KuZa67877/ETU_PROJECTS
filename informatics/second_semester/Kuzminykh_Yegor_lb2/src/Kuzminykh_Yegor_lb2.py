class Node:
    def __init__(self, data, next=None):
        self.__data = data
        self.__next__ = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next_node = 'None' if self.__next__ is None else self.__next__.__data
        return f"data: {self.__data}, next: {next_node}"


class LinkedList:
    def __init__(self, __head__=None):
        self.__head__ = __head__
        if __head__ == None:
            self.__length = 0
        else:
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        if self.__length > 0:

            n = self.__head__
            while n.__next__ is not None:
                n = n.__next__
            n.__next__ = Node(element)
        else:
            self.__head__ = Node(element)
        self.__length += 1

    def pop(self):
        if self.__length != 0:
            if self.__length==1:
                self.__head__=self.__head__.__next__
            else:
                tmp1 = self.__head__
                tmp2=tmp1.__next__
                while tmp2.__next__ is not None:
                    tmp1=tmp2
                    tmp2=tmp2.__next__
                tmp1.__next__=None
            self.__length-=1
        else:
            raise IndexError("LinkedList is empty!")


    def clear(self):
        self.__length = 0
        self.__head__ = None

    def delete_on_end(self, n):
        if 0<n<=self.__length:
            if 0 < n <= self.__length:
                if n == self.__length:
                    self.__head__ = self.__head__.__next__
                else:
                    tmp = self.__head__
                    for i in range(self.__length - n - 1):
                        tmp = tmp.__next__
                    tmp.__next__ = tmp.__next__.__next__
                self.__length -= 1
        else:
            raise KeyError("<element> doesn't exist!");
    def __str__(self):
        result = 'LinkedList[]'
        if self.__length != 0:
            array = []
            tmp = self.__head__
            while tmp is not None:
                array.append(tmp.__str__())
                tmp = tmp.__next__
            str = '; '.join(array)
            result = f'LinkedList[length = {self.__length}, [{str}]]'

        return result
