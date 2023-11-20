# Author __Pham Ngoc Hai - Harito__

# Home work week ...
# all prefix sum GPU 
# sort array vs GPU 
import numpy as np

class Maze:
    def __init__(self, rows=None, cols=None, obstacle_prob=None):
        if rows == None or cols == None or obstacle_prob == None:
            self.maze = None
            return
        random_values = np.random.rand(rows, cols)
        self.maze = np.full((rows, cols), False, dtype=bool)
        self.maze[random_values < obstacle_prob] = True

    # Change maze follow by probability and check the updated maze can have path to go or not
    def change_maze(self, prob_false_to_true, prob_true_to_false):
        is_dead_maze = 0
        shape = self.maze.shape
        for i in range(shape[0]):
            for j in range(shape[1]):
                random_value = np.random.rand()
                if not self.maze[i, j]:
                    if random_value < prob_false_to_true:
                        self.maze[i, j] = True
                    else:
                        is_dead_maze += 1
                elif self.maze[i, j] and random_value < prob_true_to_false:
                    self.maze[i, j] = False
                    is_dead_maze += 1
        return is_dead_maze == 0

    # Return a clone maze (type: Maze)
    def clone_maze(self):
        new_maze = Maze()
        new_maze.maze = np.copy(self.maze)
        return new_maze

    # Check the current position can go throw or not
    def can_pass(self, current:tuple):
        return current[0] >= 0 and current[1] >= 0 \
            and current[0] < self.maze.shape[0] \
            and current[1] < self.maze.shape[1] \
            and not self.maze[current[0], current[1]]

    # Return a list of neighbors can reach of the current position
    def neighbors(self, current:tuple):
        neighbors = []
        directions = ((-1, 0), (0, 1), (1, 0), (0, -1))
        for move in directions:
            neighbor = tuple(current[0] + move[0], current[1] + move[1])
            if self.can_pass(neighbor):
                neighbors.append(neighbor)
        return neighbors

def main():
    # Sử dụng lớp Maze
    rows = 5  # Số hàng 
    cols = 5  # Số cột
    obstacle_prob = 0.3  # Xác suất ô bị chặn

    maze_instance = Maze(rows, cols, obstacle_prob)

    # Gọi các phương thức của lớp Maze
    print("Initial Maze:")
    print(maze_instance.maze)

    is_dead_maze = maze_instance.change_maze(0.5, 0)
    print("Changed Maze:")
    print(maze_instance.maze)
    print("Is Dead Maze:", is_dead_maze)

    cloned_maze = maze_instance.clone_maze()
    print("Cloned Maze:")
    print(cloned_maze.maze)

    is_dead_maze = cloned_maze.change_maze(0.2, 0)
    print("Change cloned Maze:")
    print(cloned_maze.maze)
    print("Is Dead Maze:", is_dead_maze)

if __name__ == "__main__":
    main()
