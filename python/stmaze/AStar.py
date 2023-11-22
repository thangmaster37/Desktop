# Author __Tran Minh Duc__
import sys, os
# Get the parent directory
package_path = "./python"
# Add the parent directory to sys.path
sys.path.append(os.path.abspath(package_path))

from maze.Maze import Maze
from queue import PriorityQueue
import numpy as np

class AStar():
    def __init__(self, maze: Maze):
        self.maze = maze
        self.astar_map = []

    def astar(self, start: tuple, end: tuple):
        heuristic = lambda x, y, z, t: abs(x-z) + abs(y-t)   
        count = 0
        open_queue = PriorityQueue()
        open_set = [start]
        node_path = []
        astar_path_list = []
        open_queue.put((0, count, start))

        g_score = [[float("inf") for spot in row] for row in self.maze.maze]
        g_score[start[0]][start[1]] = 0
        f_score = [[float('inf') for spot in row] for row in self.maze.maze]
        f_score[start[0]][start[1]] = heuristic(start[0], start[1], end[0], end[1])
        
        while not open_queue.empty():
            #... tasks: Duc complete the code in here
            current_node = open_queue.get()[2]
            open_set.remove(current_node)
            if current_node == end:
                while current_node!= start:
                    astar_path_list.append(current_node)
                    current_node = open_set[current_node]
                astar_path_list.append(start)
                astar_path_list.reverse()
                break
            
            neighbors = self.maze.get_neighbors()
            for neighbor in neighbors:
                temp_g_score = g_score[current_node[0]][current_node[1]] + 1
                if temp_g_score < g_score[neighbor[0]][neighbor[1]]:
                    node_path[neighbor] = current_node
                    g_score[neighbor[0]][neighbor[1]] = temp_g_score
                    f_score[neighbor[0]][neighbor[1]] = temp_g_score + heuristic(neighbor, end)
                    if neighbor not in open_set:
                        count +=1 
                        open_queue.put(f_score[neighbor[0]][neighbor[1]], count, neighbor)
                        open_set.add(neighbor)
                        
        # transform numpy array - A* path: astar_path to a dict
        self.astar_path = []
        for node in astar_path_list:
            self.astar_path[node] = node_path[node]
        # ... tasks: Duc complete the code in here
        return self.astar_path # [start, (x,y), (a, b), ..., end] - numpy array

    def map(self):  
        return self.astar_map # a dictionary[start: (x, y), (x, y): (a, b), (a, b): ..., ...., ...: end]
    
if __name__ == "__main__":
    my_maze = Maze.array([
         [False, False, False, False, False],
         [True, True, False, True, False],
         [False, False, False, False, False],
         [False, True, True, True, False],
         [False, False, False, False, False]])
    # print(my_maze)
    # astar = AStar(my_maze)
