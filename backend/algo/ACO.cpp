#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <climits>
#include <algorithm>
#include <chrono>

#include "../Maze.cpp"

class ACO
{
private:
    int num_ants;
    int iterations;
    double pheromone_const;
    double evaporation_rate;
    double alpha;

    // struct HashPair
    // {
    //     template <class T1, class T2>
    //     std::size_t operator()(const std::pair<T1, T2> &p) const
    //     {
    //         auto hash1 = std::hash<T1>{}(p.first);
    //         auto hash2 = std::hash<T2>{}(p.second);

    //         return hash1 ^ hash2;
    //     }
    // };

    struct HashPair
    {
        template <class T1, class T2, class T3, class T4>
        std::size_t operator()(const std::pair<std::pair<T1, T2>, std::pair<T3, T4>> &p) const
        {
            auto h1 = std::hash<T1>{}(p.first.first);
            auto h2 = std::hash<T2>{}(p.first.second);
            auto h3 = std::hash<T3>{}(p.second.first);
            auto h4 = std::hash<T4>{}(p.second.second);

            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };

    std::pair<int, int> chooseNeighbor(const std::vector<std::pair<int, int>> &neighbors, const std::vector<double> &weights)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> distribution(weights.begin(), weights.end());

        return neighbors[distribution(gen)];
    }

public:
    ACO(int num_ants = 30, int iterations = 30, double pheromone_const = 1000.0, double evaporation_rate = 0.4, double alpha = 0.3)
        : num_ants(num_ants), iterations(iterations), pheromone_const(pheromone_const), evaporation_rate(evaporation_rate), alpha(alpha) {}

    std::pair<std::vector<std::pair<int, int>>, std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, double, HashPair>>
    solve_serial(Maze &maze, std::pair<int, int> start, std::pair<int, int> end)
    {
        std::vector<std::pair<int, int>> best_path;
        int best_path_length = INT_MAX;
        std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, double, HashPair> pheromone_map;

        for (int iteration = 0; iteration < iterations; ++iteration)
        {
            std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, double, HashPair> pheromone_delta;

            for (int ant = 0; ant < num_ants; ++ant)
            {
                std::pair<int, int> current = start;
                std::vector<std::pair<int, int>> path = {current};
                std::unordered_set<std::pair<std::pair<int, int>, std::pair<int, int>>, HashPair> used_trails;

                while (current != end)
                {
                    std::vector<std::pair<int, int>> neighbors = maze.getNeighbors(current);
                    std::vector<double> weights;
                    double sum_pheromone = 0.0;

                    for (const auto &neighbor : neighbors)
                    {
                        if (pheromone_map.find({current, neighbor}) != pheromone_map.end())
                        {
                            sum_pheromone += pheromone_map[{current, neighbor}];
                        }
                        else
                        {
                            sum_pheromone += 0.1;
                        }
                    }

                    for (const auto &neighbor : neighbors)
                    {
                        if (pheromone_map.find({current, neighbor}) != pheromone_map.end())
                        {
                            weights.push_back(std::pow(pheromone_map[{current, neighbor}], alpha) / sum_pheromone);
                        }
                        else
                        {
                            weights.push_back(std::pow(0.1, alpha) / sum_pheromone);
                        }
                    }

                    std::pair<int, int> pre = current;
                    current = chooseNeighbor(neighbors, weights);
                    path.push_back(current);
                    used_trails.insert({pre, current});
                }

                if (path.size() < best_path_length)
                {
                    best_path = path;
                    best_path_length = path.size();
                }

                for (const auto &trail : used_trails)
                {
                    double delta = pheromone_const / path.size();
                    pheromone_delta[trail] += delta;
                }
            }

            for (auto &trail : pheromone_map)
            {
                trail.second *= (1 - evaporation_rate);
            }

            for (const auto &delta : pheromone_delta)
            {
                pheromone_map[delta.first] += delta.second;
            }
        }

        return std::make_pair(best_path, pheromone_map);
    }

    // std::pair<std::vector<std::pair<int, int>>, std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, double, HashPair>>
    // solve_parallel(Maze &maze, std::pair<int, int> start, std::pair<int, int> end)
    // {

    // }
};

int main()
{
    Maze myMaze({25, 25});
    std::pair<std::pair<int, int>, std::pair<int, int>> startEnd = myMaze.selectStartAndEnd();
    myMaze.print();

    ACO myACO;

    auto start = std::chrono::high_resolution_clock::now();
    auto result = myACO.solve_serial(myMaze, startEnd.first, startEnd.second);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Thời gian thực hiện tuần tự: " << duration.count() << " giây\n";

    // Print path
    std::cout << "Path: ";
    for (const auto &point : result.first)
    {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << std::endl;

    // Print map
    std::cout << "Map: ";
    for (const auto &point : result.second)
    {
        std::cout << "[ (" << point.first.first.first << ", " << point.first.first.second << ") -> (" << point.first.second.first << ", " << point.first.second.second << ") : " << point.second << " ]\n";
    }
    std::cout << std::endl;

    return 0;
}
