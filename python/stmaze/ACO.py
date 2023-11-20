# Author __Luong Duc Anh__
from maze import Maze

class ACO():
    def __init__(self, maze: Maze):
        self.aco_path = self.solve(maze)

    def aco(maze:Maze):
        # ...
        # return a tuple of (aco_path, pheromone_map)
        return 
    
    def solve(maze: Maze):
        return # [start, (x,y), (a, b), ..., end] - numpy array <=> ACO.aco()[0]
    
    def to_dict(): 
        # transform numpy array - ACO path: self.aco_path to a dict

        return # a dictionary about pheromone map <=> ACO.aco()[1``]