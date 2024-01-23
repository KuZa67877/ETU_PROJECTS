states = {
    'q': {  # считываем до первой а
        'a': ['a', 1, 'q_a'],
        'b': ['b', 1, 'q'],
        'c': ['c', 1, 'q'],
        ' ': [' ', 1, 'q']
    },
    'q_a': {
        'a': ['a', -1, 'q1'],
        'b': ['b', -1, 'q2'],
        'c': ['c', -1, 'q3'],
        ' ': [' ', -1, 'q1']
    },
    'q1': {
        'a': ['a', -1, 'q1'],
        'b': ['b', -1, 'q1'],
        'c': ['c', -1, 'q1'],
        ' ': [' ', 1, 'q_nach1']
    },
    'q2': {
        'a': ['a', -1, 'q2'],
        'b': ['b', -1, 'q2'],
        'c': ['c', -1, 'q2'],
        ' ': [' ', 1, 'q_nach2']
    },
    'q3': {
        'a': ['a', -1, 'q3'],
        'b': ['b', -1, 'q3'],
        'c': ['c', -1, 'q3'],
        ' ': [' ', 1, 'q_nach3']
    },
    'q4': {
        'a': ['a', -1, 'q4'],
        'b': ['b', -1, 'q4'],
        'c': ['c', -1, 'q4'],
        ' ': [' ', 1, 'q_nach1']

    },

    'q_nach1': {
        'a': ['a', 1, 'q_nach1'],
        'b': ['b', 1, 'q_nach1'],
        'c': ['c', -1, 'q1_zamena'],
        ' ': [' ', 1, 'q_nach1']

    },
    'q_nach2': {
        'a': ['a', 1, 'q_nach2'],
        'b': ['b', 1, 'q_nach2'],
        'c': ['c', -1, 'q2_zamena'],
        ' ': [' ', 1, 'q_nach2']

    },
    'q_nach3': {
        'a': ['a', 1, 'q_nach3'],
        'b': ['b', 1, 'q_nach3'],
        'c': ['c', -1, 'q3_zamena'],
        ' ': [' ', 1, 'q_nach3']

    },
    'q1_zamena': {
        'a': ['a', 0, 'q_end'],
        'b': ['a', 0, 'q_end'],
        'c': ['a', 0, 'q_end'],
        ' ': ['a', 0, 'q_end']
    },
    'q2_zamena': {
        'a': ['b', 0, 'q_end'],
        'b': ['b', 0, 'q_end'],
        'c': ['b', 0, 'q_end'],
        ' ': ['b', 0, 'q_end']
    },
    'q3_zamena': {
        'a': ['c', 0, 'q_end'],
        'b': ['c', 0, 'q_end'],
        'c': ['c', 0, 'q_end'],
        ' ': ['c', 0, 'q_end']
    }
}
digit = list(input())
index = 0
q = 'q'
while q != 'q_end':
    symbol = states[q][digit[index]][0]
    delta = states[q][digit[index]][1]
    state = states[q][digit[index]][2]
    digit[index] = symbol
    index += delta
    q = state

print(''.join(digit))

