# Author __Tran Minh Duc__
import sys, os
# Get the parent directory
package_path = "./python"
# Add the parent directory to sys.path
sys.path.append(os.path.abspath(package_path))

from maze.Maze import Maze
from queue import PriorityQueue
class AStar():
    def __init__(self, maze: Maze):
        self.maze = maze

    def astar(self, start: tuple, end: tuple):
        
        count = 0
        open_queue = PriorityQueue()
        open_set = {start}
        node_path = dict()
        
        heuristic = lambda x, y: abs(x[0] - y[0]) + abs(x[1] - y[1])
        
        open_queue.put((0, count, start))

        g_score = [[float("inf") for spot in row] for row in self.maze.array()]
        g_score[start[0]][start[1]] = 0
        f_score = [[float('inf') for spot in row] for row in self.maze.array()]
        f_score[start[0]][start[1]] = heuristic(start, end)
        
        while not open_queue.empty():
            #... tasks: Duc complete the code in here
            current_node = open_queue.get()[2]
            open_set.remove(current_node)
            if current_node == end:
                astar_path = []
                while current_node!= start:
                    astar_path.append(current_node)
                    current_node = open_set[current_node]
                astar_path.append(start)
                astar_path.reverse()
                return astar_path
            
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
        # ... tasks: Duc complete the code in here
        return astar_path # [start, (x,y), (a, b), ..., end] - numpy array

    def map(self):  
        return self.astar_map # a dictionary{start: (x, y), (x, y): (a, b), (a, b): ..., ...., ...: end}
