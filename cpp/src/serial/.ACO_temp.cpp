#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct Ant
{
    std::pair<int, int> position;
    std::vector<std::pair<int, int>> path;
    double pathCost;

    Ant(std::pair<int, int> startPos) : position(startPos), pathCost(0.0)
    {
        path.push_back(startPos);
    }
};

// Function to check if a given cell is valid (inside the maze and not blocked)
bool isValid(int x, int y, int m, int n, const std::vector<std::vector<bool>> &maze)
{
    return x >= 0 && y >= 0 && x < m && y < n && !maze[x][y];
}

// Function to initialize pheromone levels on all edges
std::vector<std::vector<double>> initializePheromones(int m, int n, double initialPheromone)
{
    return std::vector<std::vector<double>>(m, std::vector<double>(n, initialPheromone));
}

// Function to update pheromone levels based on ant paths
void updatePheromones(std::vector<std::vector<double>> &pheromones, const std::vector<Ant> &ants, double evaporationRate)
{
    for (auto &row : pheromones)
    {
        for (double &pheromone : row)
        {
            pheromone *= (1.0 - evaporationRate);
        }
    }

    for (const Ant &ant : ants)
    {
        double pheromoneToAdd = 1.0 / ant.pathCost; // Inverse of path cost
        for (size_t i = 0; i < ant.path.size() - 1; ++i)
        {
            int x = ant.path[i].first;
            int y = ant.path[i].second;
            int nextX = ant.path[i + 1].first;
            int nextY = ant.path[i + 1].second;
            pheromones[x][y] += pheromoneToAdd;
            pheromones[nextX][nextY] += pheromoneToAdd;
        }
    }
}

// Function to select the next move for an ant based on pheromone levels and heuristics
std::pair<int, int> selectNextMove(int x, int y, int m, int n, const std::vector<std::vector<bool>> &maze,
                                   const std::vector<std::vector<double>> &pheromones, double alpha)
{
    // Directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    std::vector<std::pair<int, int>> possibleMoves;
    double totalProbability = 0.0;

    // Calculate probabilities for each possible move
    for (int i = 0; i < 4; ++i)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        // Check if the move is valid
        if (isValid(newX, newY, m, n, maze))
        {
            double pheromone = pheromones[newX][newY];
            double probability = std::pow(pheromone, alpha);
            possibleMoves.push_back({newX, newY});
            totalProbability += probability;
        }
    }

    // Randomly select a move based on probabilities
    double randomValue = static_cast<double>(rand()) / RAND_MAX * totalProbability;
    double cumulativeProbability = 0.0;

    for (const auto &move : possibleMoves)
    {
        int newX = move.first;
        int newY = move.second;
        double moveProbability = std::pow(pheromones[newX][newY], alpha);
        cumulativeProbability += moveProbability;

        if (cumulativeProbability >= randomValue)
        {
            return move;
        }
    }

    // Default case (should not reach here)
    return {x, y};
}

// Function to perform ACO
std::vector<std::pair<int, int>> ACO(std::vector<std::vector<bool>> &maze, int m, int n,
                                     std::pair<int, int> start, std::pair<int, int> end,
                                     int numAnts = 30, double iterations = 30, double pheromoneConst = 1000.0,
                                     double evaporationRate = 0.3, double alpha = 0.6)
{
    std::vector<std::pair<int, int>> path;

    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create ants
    std::vector<Ant> ants;
    for (int i = 0; i < numAnts; ++i)
    {
        ants.push_back(Ant(start));
    }

    // Initialize pheromones
    std::vector<std::vector<double>> pheromones = initializePheromones(m, n, pheromoneConst);

    // ACO iterations
    for (int iter = 0; iter < iterations; ++iter)
    {
        // Move each ant
        for (Ant &ant : ants)
        {
            while (ant.position != end)
            {
                auto nextMove = selectNextMove(ant.position.first, ant.position.second, m, n, maze, pheromones, alpha);
                ant.position = nextMove;
                ant.path.push_back(nextMove);
                ant.pathCost += 1.0; // Assuming unit cost for each move
            }
        }

        // Update pheromones based on ant paths
        updatePheromones(pheromones, ants, evaporationRate);

        // Reset ants for the next iteration
        for (Ant &ant : ants)
        {
            ant.position = start;
            ant.path.clear();
            ant.path.push_back(start);
            ant.pathCost = 0.0;
        }
    }

    // Find the best path among all ants
    double minPathCost = std::numeric_limits<double>::infinity();
    const Ant *bestAnt = nullptr;

    for (const Ant &ant : ants)
    {
        if (ant.pathCost < minPathCost)
        {
            minPathCost = ant.pathCost;
            bestAnt = &ant;
        }
    }

    // Extract the best path
    if (bestAnt)
    {
        path = bestAnt->path;
    }

    return path;
}

int main()
{
    // Example usage
    int m = 5;
    int n = 5;
    // (0, 0) (0, 1) (0, 2) (1, 2) (2, 2) (2, 3) (2, 4) (3, 4) (4, 4) (4, 3)
    std::vector<std::vector<bool>> maze = {
        {false, false, false, false, false},
        {true,  true,  false, true,  false},
        {false, false, false, false, false},
        {false, true,  true,  true,  false},
        {false, false, false, false, false}
    };
    // std::vector<std::vector<bool>> maze = {
    //     {true, false, false, false, false},
    //     {true, true, true, true, false},
    //     {false, false, false, true, false},
    //     {false, true, true, true, false},
    //     {false, false, false, true, false}};

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {4, 3};

    std::vector<std::pair<int, int>> path = ACO(maze, m, n, start, end);

    // Print the path
    std::cout << "Path:\n";
    for (const auto &point : path)
    {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << "\n";

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>
// #include <cmath>
// #include <limits>

// struct Ant
// {
//     std::pair<int, int> position;
//     std::vector<std::pair<int, int>> path;
//     double pathCost;

//     Ant(std::pair<int, int> startPos) : position(startPos), pathCost(0.0)
//     {
//         path.push_back(startPos);
//     }
// };

// // Function to check if a given cell is valid (inside the maze and not blocked)
// bool isValid(int x, int y, int m, int n, const std::vector<std::vector<bool>> &maze)
// {
//     return x >= 0 && y >= 0 && x < m && y < n && !maze[x][y];
// }

// // Function to initialize pheromone levels on all edges
// std::vector<std::vector<double>> initializePheromones(int m, int n, double initialPheromone)
// {
//     return std::vector<std::vector<double>>(m, std::vector<double>(n, initialPheromone));
// }

// // Function to update pheromone levels based on ant paths
// void updatePheromones(std::vector<std::vector<double>> &pheromones, const std::vector<Ant> &ants, double evaporationRate)
// {
//     for (auto &row : pheromones)
//     {
//         for (double &pheromone : row)
//         {
//             pheromone *= (1.0 - evaporationRate);
//         }
//     }

//     for (const Ant &ant : ants)
//     {
//         double pheromoneToAdd = 1.0 / ant.pathCost; // Inverse of path cost
//         for (size_t i = 0; i < ant.path.size() - 1; ++i)
//         {
//             int x = ant.path[i].first;
//             int y = ant.path[i].second;
//             int nextX = ant.path[i + 1].first;
//             int nextY = ant.path[i + 1].second;
//             pheromones[x][y] += pheromoneToAdd;
//             pheromones[nextX][nextY] += pheromoneToAdd;
//         }
//     }
// }

// // Function to select the next move for an ant based on pheromone levels and heuristics
// std::pair<int, int> selectNextMove(int x, int y, int m, int n, const std::vector<std::vector<bool>> &maze,
//                                    const std::vector<std::vector<double>> &pheromones, double alpha)
// {
//     // Directions: up, down, left, right
//     int dx[] = {-1, 1, 0, 0};
//     int dy[] = {0, 0, -1, 1};

//     std::vector<std::pair<int, int>> possibleMoves;
//     double totalProbability = 0.0;

//     // Calculate probabilities for each possible move
//     for (int i = 0; i < 4; ++i)
//     {
//         int newX = x + dx[i];
//         int newY = y + dy[i];

//         // Check if the move is valid
//         if (isValid(newX, newY, m, n, maze))
//         {
//             double pheromone = pheromones[newX][newY];
//             double probability = std::pow(pheromone, alpha);
//             possibleMoves.push_back({newX, newY});
//             totalProbability += probability;
//         }
//     }

//     // Randomly select a move based on probabilities
//     double randomValue = static_cast<double>(rand()) / RAND_MAX * totalProbability;
//     double cumulativeProbability = 0.0;

//     for (const auto &move : possibleMoves)
//     {
//         int newX = move.first;
//         int newY = move.second;
//         double moveProbability = std::pow(pheromones[newX][newY], alpha);
//         cumulativeProbability += moveProbability;

//         if (cumulativeProbability >= randomValue)
//         {
//             return move;
//         }
//     }

//     // Default case (should not reach here)
//     return {x, y};
// }

// // Function to perform ACO
// std::vector<std::pair<int, int>> ACO(std::vector<std::vector<bool>> &maze, int m, int n,
//                                      std::pair<int, int> start, std::pair<int, int> end,
//                                      int numAnts = 30, double iterations = 30, double pheromoneConst = 1000.0,
//                                      double evaporationRate = 0.3, double alpha = 0.6)
// {
//     std::vector<std::pair<int, int>> path;

//     // Initialize random seed
//     srand(static_cast<unsigned int>(time(nullptr)));

//     // Create ants
//     std::vector<Ant> ants;
//     for (int i = 0; i < numAnts; ++i)
//     {
//         ants.push_back(Ant(start));
//     }

//     // Initialize pheromones
//     std::vector<std::vector<double>> pheromones = initializePheromones(m, n, pheromoneConst);

//     // ACO iterations
//     for (int iter = 0; iter < iterations; ++iter)
//     {
//         // Move each ant
//         for (Ant &ant : ants)
//         {
//             while (ant.position != end)
//             {
//                 auto nextMove = selectNextMove(ant.position.first, ant.position.second, m, n, maze, pheromones, alpha);
//                 ant.position = nextMove;
//                 ant.path.push_back(nextMove);
//                 ant.pathCost += maze[nextMove.first][nextMove.second] ? std::numeric_limits<double>::infinity() : 1.0;
//             }
//         }

//         // Update pheromones based on ant paths
//         updatePheromones(pheromones, ants, evaporationRate);

//         // Reset ants for the next iteration
//         for (Ant &ant : ants)
//         {
//             ant.position = start;
//             ant.path.clear();
//             ant.path.push_back(start);
//             ant.pathCost = 0.0;
//         }
//     }

//     // Find the best path among all ants
//     double minPathCost = std::numeric_limits<double>::infinity();
//     const Ant *bestAnt = nullptr;

//     for (const Ant &ant : ants)
//     {
//         if (ant.pathCost < minPathCost)
//         {
//             minPathCost = ant.pathCost;
//             bestAnt = &ant;
//         }
//     }

//     // Extract the best path
//     if (bestAnt)
//     {
//         path = bestAnt->path;
//     }

//     return path;
// }

// int main()
// {
//     // Example usage
//     int m = 5;
//     int n = 5;
//     // (0, 0) (0, 1) (0, 2) (1, 2) (2, 2) (2, 3) (2, 4) (3, 4) (4, 4) (4, 3)
//     // std::vector<std::vector<bool>> maze = {
//     //     {false, false, false, false, false},
//     //     {true,  true,  false, true,  false},
//     //     {false, false, false, false, false},
//     //     {false, true,  true,  true,  false},
//     //     {false, false, false, false, false}
//     // };
//     std::vector<std::vector<bool>> maze = {
//         {true, false, false, false, false},
//         {true,  true,  true, true,  false},
//         {false, false, false, true, false},
//         {false, true,  true,  true,  false},
//         {false, false, false, true, false}
//     };

//     std::pair<int, int> start = {0, 0};
//     std::pair<int, int> end = {4, 3};

//     std::vector<std::pair<int, int>> path = ACO(maze, m, n, start, end);

//     // Print the path
//     std::cout << "Path:\n";
//     for (const auto &point : path)
//     {
//         std::cout << "(" << point.first << ", " << point.second << ") ";
//     }
//     std::cout << "\n";

//     return 0;
// }
