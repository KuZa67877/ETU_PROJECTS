import numpy as np
import random


def coin_flip(p):
    return random.choice([0, 1]) if random.random() < p else 1

def one_game(probability_a, probability_b):
    return coin_flip(probability_a), coin_flip(probability_b)

game_field = np.array([[2, -3], [-1, 2]])

def get_game_points(experiment):
    return game_field[experiment[0]][experiment[1]]

def fill_vector_of_games(probability_a, probability_b):
    return np.array([one_game(probability_a, probability_b) for _ in range(100)])

def all_game_points(experiments):
    return np.array([get_game_points(experiment) for experiment in experiments])


def math_waiting(points, occurrences):
   return np.multiply(points, occurrences).sum()

def dispersion(points, occurrences):
   mean = math_waiting(points, occurrences)
   deviation = np.subtract(points, mean)
   squared_deviation = np.square(deviation)
   return np.multiply(occurrences, squared_deviation).sum()


def statistic(probability_a, probability_b):
   experiment = fill_vector_of_games(probability_a, probability_b)
   points = all_game_points(experiment)
   total_points = points.sum()
   print(f"Количество выигранных очков игроком А - {total_points}")
   avg_points = points.mean()
   print(f"Среднее количество очков за игру - {avg_points}")
   occ = np.array([probability_a * probability_b, (1 - probability_b) * probability_a, (1 - probability_a) * probability_b, (1 - probability_a) * (1 - probability_b)])
   game_scores = game_field.flatten()
   expected_score = math_waiting(game_scores, occ)
   print(f"Математическое ожидание - {expected_score}")
   std_dev = points.std()
   #print(f"Std dev: {std_dev}")
   disp = dispersion(game_scores, occ)
   print(f"Дисперсия - {disp}")
   theoretical_skill_level = np.sqrt(disp)
   print(f"СКО - {theoretical_skill_level}")

