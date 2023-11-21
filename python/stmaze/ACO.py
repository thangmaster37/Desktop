# Author __Luong Duc Anh__
import sys
import os

package_path = "./python"
sys.path.append(os.path.abspath(package_path))

from maze.Maze import Maze
from collections import defaultdict
import random
import math

class ACO():
    def __init__(self,
                 num_ants=1,
                 iterations=30,
                 pheromone_const=1000.0,
                 evaporation_rate=0.4,
                 alpha=0.3):
        self.num_ants = num_ants
        self.iterations = iterations
        self.pheromone_const = pheromone_const
        self.evaporation_rate = evaporation_rate
        self.alpha = alpha

    def aco(self, maze: Maze, start: tuple, end: tuple):
        best_path = None
        best_path_length = float('inf')
        pheromone_map = defaultdict(lambda: 0.1)
        for _ in range(self.iterations):
            pheromone_delta = defaultdict(lambda: 0.1)
            for _ in range(self.num_ants):
                current = start
                path = [current]
                used_trails = set()
                while current != end:
                    neighbors = maze.get_neighbors(current)
                    weights = []
                    sum_pheromone = 0.0
                    for neighbor in neighbors:
                        sum_pheromone += pheromone_map[(
                            current, neighbor)]
                    for neighbor in neighbors:
                        weights.append(
                            math.pow(pheromone_map[(current, neighbor)], self.alpha)/sum_pheromone)
                    pre = current
                    current = random.choices(neighbors, weights)[0]
                    path.append(current)
                    used_trails.add((pre, current))
                if len(path) < best_path_length:
                    best_path = path
                    best_path_length = len(path)
                for trail in used_trails:
                    delta = self.pheromone_const / len(path)
                    pheromone_delta[trail] += delta
            for trail in pheromone_map.keys():
                pheromone_map[trail] *= (1 - self.evaporation_rate)
            for trail, value in pheromone_delta.items():
                pheromone_map[trail] += value
        return best_path, pheromone_map


if __name__ == "__main__":
    my_maze = Maze.array([[False, False, False, False, False, False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False,
                              False, False, False, False, False],
                          [False, False, False, False, False, False, False, False, False, False]])
    # print(my_maze)
    aco = ACO()
    print(aco.aco(my_maze, (0, 0), (5, 5))[0])
