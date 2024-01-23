from main import HashTable

def test_add_and_find_value():
   ht = HashTable(5)
   ht.add('test_key', 'test_value')
   assert ht.find_value('test_key') == 'test_value'

def test_delete_key():
   ht = HashTable(5)
   ht.add('test_key', 'test_value')
   ht.delete('test_key')
   assert ht.find_value('test_key') is None

def test_resize_table():
   ht = HashTable(2)
   ht.add('test_key1', 'test_value1')
   ht.add('test_key2', 'test_value2')
   assert ht.capacity == 4

def test_hash_collision():
   ht = HashTable(2)
   ht.add('test_key1', 'test_value1')
   ht.add('test_key2', 'test_value2')
   assert ht.find_value('test_key1') == 'test_value1'
   assert ht.find_value('test_key2') == 'test_value2'
