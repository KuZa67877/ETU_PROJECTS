from main import rabin_karp_search

def test_rabin_karp_search_no_match():
   pattern = "abc"
   text = "def"
   assert rabin_karp_search(pattern, text) == []

def test_rabin_karp_search_one_match():
   pattern = "abc"
   text = "abcdef"
   assert rabin_karp_search(pattern, text) == [0]

def test_rabin_karp_search_multiple_matches():
   pattern = "abc"
   text = "abcabcabc"
   assert rabin_karp_search(pattern, text) == [0, 3, 6]

def test_rabin_karp_search_overlapping_matches():
   pattern = "abc"
   text = "abcabcabc"
   assert rabin_karp_search(pattern, text) == [0, 3, 6]