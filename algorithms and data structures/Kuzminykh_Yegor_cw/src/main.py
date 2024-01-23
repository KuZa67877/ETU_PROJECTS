class HashTableEntry:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self, capacity, max_load_factor=0.7):
        self.capacity = capacity
        self.max_load_factor = max_load_factor
        self.size = 0
        self.table = [None] * capacity

    def calculate_hash(self, key):
        return hash(key) % self.capacity
        # Примеры других хэш-функций
        # base_hash = sum(ord(char) for char in str(key))
        # random_offset = random.randint(0, self.capacity - 1)
        # return (base_hash + random_offset) % self.capacity
        # return 0

    def add(self, key, value):
        index = self.calculate_hash(key)
        if self.table[index] is None:
            self.table[index] = HashTableEntry(key, value)
            self.size += 1
        else:
            new_entry = HashTableEntry(key, value)
            new_entry.next = self.table[index]
            self.table[index] = new_entry
            self.size += 1

        if self.size / self.capacity > self.max_load_factor:
            self.resize_table()

    def find_value(self, key):
        index = self.calculate_hash(key)
        current = self.table[index]
        while current:
            if current.key == key:
                return current.value
            current = current.next

    def resize_table(self):
        old_table = self.table
        self.capacity *= 2
        self.table = [None] * self.capacity
        self.size = 0

        for entry in old_table:
            current = entry
            while current:
                self.add(current.key, current.value)
                current = current.next

    def delete(self, key):
        index = self.calculate_hash(key)
        previous = None
        current = self.table[index]
        while current:
            if current.key == key:
                if previous:
                    previous.next = current.next
                else:
                    self.table[index] = current.next
                self.size -= 1
                return
            previous = current
            current = current.next
