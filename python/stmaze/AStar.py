# Author __Tran Minh Duc__
import sys, os
# Get the parent directory
package_path = "./python"
# Add the parent directory to sys.path
sys.path.append(os.path.abspath(package_path))

from maze.Maze import Maze

class AStar():
    def __init__(self, maze: Maze):
        self.maze = maze
        self.astar_map = {}

    def heuristic():
        # ... tasks: Duc complete the code in here
        pass

    def astar(self, start: tuple, end: tuple):
        self.astar_map = {}     # restart the value of self.astar_map
        astar_path = None
        # transform numpy array - A* path: astar_path to a dict
        # ... tasks: Duc complete the code in here
        return astar_path # [start, (x,y), (a, b), ..., end] - numpy array

    def map(self):  
        return self.astar_map # a dictionary{start: (x, y), (x, y): (a, b), (a, b): ..., ...., ...: end}