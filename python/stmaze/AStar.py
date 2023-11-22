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
        self.astar_map = {}

    def astar(self, start: tuple, end: tuple):
        heuristic = lambda x, y: abs(x[0] - y[0]) + abs(x[1] - y[1]) 
        count = 0
        open_queue = PriorityQueue()
        open_set = {start}
        node_path = {}
        self.astar_map = {}
        open_queue.put((0, count, start))

        g_score = np.full(self.maze.rows, self.maze.cols, float('inf'))
        g_score[start[0], start[1]] = 0
        f_score = np.full(self.maze.rows, self.maze.cols, float('inf'))
        f_score[start[0], start[1]] = heuristic(start, end)
        
        while not open_queue.empty():
            #... tasks: Duc complete the code in here
            current_node = open_queue.get()[2]
            open_set.remove(current_node)
            if current_node == end:
                while current_node!= start:
                    self.astar_map.add(current_node)
                    current_node = open_set[current_node]
                self.astar_map.append(start)
                self.astar_map.reverse()
                break
            
            neighbors = self.maze.get_neighbors(current_node)
            for neighbor in neighbors:
                temp_g_score = g_score[current_node[0], current_node[1]] + 1
                if temp_g_score < g_score[neighbor[0], neighbor[1]]:
                    node_path[neighbor] = current_node
                    g_score[neighbor[0], neighbor[1]] = temp_g_score
                    f_score[neighbor[0], neighbor[1]] = temp_g_score + heuristic(neighbor, end)
                    if neighbor not in open_set:
                        count +=1 
                        open_queue.put(f_score[neighbor[0], neighbor[1]], count, neighbor)
                        open_set.append(neighbor)
                        
        # transform numpy array - A* path: astar_path to a dict
        # ... tasks: Duc complete the code in here
        
        
        return astar_path # [start, (x,y), (a, b), ..., end] - numpy array

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
    astar = AStar(my_maze)
    # print(astar.astar((0,0), (4,4)))
