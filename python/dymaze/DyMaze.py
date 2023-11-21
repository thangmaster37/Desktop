# Author __Pham Ngoc Hai - Harito__
import sys, os
# Get the parent directory
package_path = "./python"
# Add the parent directory to sys.path
sys.path.append(os.path.abspath(package_path))

from maze.Maze import Maze

class DyMaze(Maze):
    # Step 0. Prepare maze
    # Create maze
    # Choose start point, end point
    # Prepare n - objects will start from start point to end point

    # Step 1. Prepare astar_map - the astar optimize path and aco_map - the pheromone map
    # astar_map
    # aco_map

    # Step 2. Moving objects to end point & Update maze at the same time
    # Write the move of ech object and each stage of maze when it change
    # (Every one step of each object)
    # Stop condition: 
    #   |___N - objects come end point success
    #   |___Maze have no more path to go
    #       => Number object come end point + Number object stuck in maze == N
    # Read the data be write and display
    pass