# Author __Tran Minh Duc__
# Get the parent directory
import sys
import os
package_path = "./python"
# Add the parent directory to sys.path
sys.path.append(os.path.abspath(package_path))

import numpy as np
from queue import PriorityQueue
from maze.Maze import Maze



class AStar():
    def astar(self, maze: Maze, start: tuple, end: tuple):
        def heuristic(p1, p2): return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
        g_score = np.full((maze.rows, maze.cols), np.iinfo(np.int32).max, dtype=np.int32)
        g_score[start] = 0
        f_score = np.full((maze.rows, maze.cols), np.iinfo(np.int32).max, dtype=np.int32)
        f_score[start] = heuristic(start, end)
        
        open = PriorityQueue()
        open.put((heuristic(start, end), heuristic(start, end), start))
        a_path = {}
        
        while not open.empty():
            current = open.get()[2]
            if current == end:
                break
            neighbors = maze.get_neighbors(current)
            for neighbor in neighbors:
                temp_g_score = g_score[current] + 1
                temp_f_score = temp_g_score + heuristic(neighbor, end)
                
                if temp_f_score < f_score[neighbor]:
                    g_score[neighbor] = temp_g_score
                    f_score[neighbor] = temp_f_score
                    open.put((temp_f_score, heuristic(neighbor, end), neighbor))
                    a_path[neighbor] = current
        fwd_path = {}
        cell = end
        path = [end]
        while cell != start:
            fwd_path[a_path[cell]] = cell
            path.insert(0, a_path[cell])
            cell = a_path[cell]
        return path, fwd_path


if __name__ == "__main__":
    my_maze = Maze.array([
        [False, False, False, False, False],
        [True, True, False, True, False],
        [False, False, False, False, False],
        [False, True, True, True, False],
        [False, False, False, False, False]])
    # print(my_maze)
    astar = AStar()
    print(astar.astar(my_maze, (0, 0), (4, 4))[0])
