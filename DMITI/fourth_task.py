import numpy
from main import *
print("#4.1")
pA = 1 / 2
pB = 1 / 4
balls = np.array([10, 10])
for _ in range(100):
    my_experiment = one_game(pA, pB)
    points = get_game_points(my_experiment)
    if points > 0:
        balls[my_experiment[0]] += points
    pA = balls[0] / balls.sum()
print(f"Вероятность выбора строчки 1 игроком A : {1 - pA}")
statistic(pA, pB)
print("#4.2")
pA = 1 / 2
pB = 1 / 4
balls = np.array([100, 100])
for _ in range(100):
    my_experiment = one_game(pA, pB)
    points = get_game_points(my_experiment)
    if points < 0:
        balls[my_experiment[0]] += points
    pA = balls[0] / balls.sum()
print(f"Вероятность выбора строчки 1 игроком B: {1 - pA}")
statistic(pA, pB)

print("#4.3")
pB = 1 / 2
balls_B = np.array([10, 10])
pA = 1 / 2
balls_A = np.array([10, 10])
for _ in range(100):
    my_experiment = one_game(pA, pB)
    points = get_game_points(my_experiment)
    if points > 0:
        balls_A[my_experiment[0]] += points
    elif points < 0:
        balls_B[my_experiment[1]] += -points
    pA = balls_A[0] / balls_A.sum()
    pB = balls_B[0] / balls_B.sum()
print(f"Вероятность выбора строчки 1 игроком A {1 - pA}")
print(f"Вероятность выбора строчки 1 игроком B {1 - pB}")
statistic(pA, pB)
