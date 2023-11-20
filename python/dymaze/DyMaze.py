# Author __Pham Ngoc Hai - Harito__
import sys, os
# Get the parent directory
package_path = "./python"
# Add the parent directory to sys.path
sys.path.append(os.path.abspath(package_path))

from maze.Maze import Maze

class DyMaze(Maze):
    pass