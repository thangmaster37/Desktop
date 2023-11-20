# Author __Tran Minh Duc__
from maze import Maze


def astar_path(maze: Maze):
    return None # [start, (x,y), (a, b), ..., end] - numpy array

def map(maze: Maze): 
    astar_path = astar_path(maze)
    # transform numpy array - A* path: self.astar_path to a dict
    
    return None # a dictionary{start: (x, y), (x, y): (a, b), (a, b): ..., ...., ...: end}