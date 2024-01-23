#python
def rabin_karp_search(pattern, text):
  d = 256
  q = 101

  M = len(pattern)
  N = len(text)

  p = 0
  t = 0
  h = 1

  for i in range(M - 1):
      h = (h * d) % q

  for i in range(M):
      p = (d * p + ord(pattern[i])) % q
      t = (d * t + ord(text[i])) % q

  indices = []
  for i in range(N - M + 1):
      if p == t:
          for j in range(M):
              if text[i + j] != pattern[j]:
                break
          else:
              indices.append(i)

      if i < N - M:
          t = (d * (t - ord(text[i]) * h) + ord(text[i + M])) % q

          if t < 0:
              t = (t + q)

  return indices

a = input()
b = input()
print(' '.join(map(str, rabin_karp_search(a, b))))
