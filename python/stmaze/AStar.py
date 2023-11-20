# Author __Tran Minh Duc__
from maze import Maze

class AStar():
    def __init__(self, maze: Maze):
        self.astar_path = self.solve(maze)

    def solve(maze: Maze):
        return # [start, (x,y), (a, b), ..., end] - numpy array
    
    def map(): 
        # transform numpy array - A* path: self.astar_path to a dict
        
        return # a dictionary{start: (x, y), (x, y): (a, b), (a, b): ..., ...., ...: end}