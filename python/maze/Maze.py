# Home work week ...
# all prefix sum GPU 
# sort array vs GPU 
import numpy as np

class Maze:
    def __init__(self, rows, cols, obstacle_prob):
        self.rows = rows
        self.cols = cols
        self.obstacle_prob = obstacle_prob
        self.maze = self._create_maze()

    def _create_maze(self):
        maze = np.full((self.rows, self.cols), False, dtype=bool)
        random_values = np.random.rand(self.rows, self.cols)
        maze[random_values < self.obstacle_prob] = True
        return maze

    def change_maze(self, prob_false_to_true, prob_true_to_false):
        is_live_maze = True
        for i in range(self.rows):
            for j in range(self.cols):
                random_value = np.random.rand()
                if not self.maze[i, j] and random_value < prob_false_to_true:
                    self.maze[i, j] = True
                    is_live_maze ^= True
                elif self.maze[i, j] and random_value < prob_true_to_false:
                    self.maze[i, j] = False
                    is_live_maze ^= False
        return is_live_maze

    def clone_maze(self):
        return np.copy(self.maze)

    def change_clone_maze(self, prob_false_to_true, prob_true_to_false):
        new_maze = self.clone_maze()
        for i in range(self.rows):
            for j in range(self.cols):
                random_value = np.random.rand()
                if not new_maze[i, j] and random_value < prob_false_to_true:
                    new_maze[i, j] = True
                elif new_maze[i, j] and random_value < prob_true_to_false:
                    new_maze[i, j] = False
        return new_maze

# Sử dụng lớp Maze
rows = 5  # Số hàng
cols = 5  # Số cột
obstacle_prob = 0.3  # Xác suất ô bị chặn

maze_instance = Maze(rows, cols, obstacle_prob)

# Gọi các phương thức của lớp Maze
print("Initial Maze:")
print(maze_instance.maze)

is_live_maze = maze_instance.change_maze(0.5, 0)
print("Changed Maze:")
print(maze_instance.maze)
print("Is Live Maze:", is_live_maze)

cloned_maze = maze_instance.clone_maze()
print("Cloned Maze:")
print(cloned_maze)

new_maze = maze_instance.change_clone_maze(0.5, 0)
print("New Maze:")
print(new_maze)
