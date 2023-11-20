# Author __Luong Duc Anh__
from maze import Maze

class ACO():
    def aco_algo(maze: Maze):
        # ...
        # return a tuple of (aco_path, pheromone_map)
        return (0, 0)
    
    def aco_path(maze: Maze):
        # [start, (x,y), (a, b), ..., end] - numpy array <=> ACO.aco_algo()[0]
        return aco_algo(maze)[0]     
    
    def map(maze: Maze): 
        # a dictionary about pheromone map <=> ACO.aco_algo()[1]
        return 