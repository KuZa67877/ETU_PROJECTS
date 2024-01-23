import numpy as np
import math
from numpy import linalg

def check_crossroad(robot, point1, point2, point3, point4):
    if (robot[0]>=point1[0]) and (robot[0]<=point2[0])and (robot[1]>=point2[1]) and (robot[1]<=point3[1]):
        return True
    else:
        return False


def check_collision(coefficients):
    answers = []
    rows,_=coefficients.shape ## возвращение кортежа во избежание ошибки
    matrix = np.delete(coefficients,2,1)
    for i in range(0,rows):
        for j in range(0,rows):
            if np.linalg.matrix_rank(np.vstack([matrix[i],matrix[j]]))==2:
                answers.append((i,j))
    return answers


def check_path(points_list):
    answer=0
    for i in range(len(points_list)-1):
        first=points_list[i]
        second = points_list[i+1]
        answer+=math.sqrt(abs(first[0]-second[0])**2+abs(first[1]-second[1])**2)
    return round(answer,2)
