// __Author: Pham Ngoc Hai _ Harito__
// #pragma once
#include <vector>
#include <utility>
#include "Maze.cpp"
#include "Object.cpp"
#include "algo/AStar.cpp"
#include "algo/ACO.cpp"

// Thuật toán

int main()
{
    // 0. Prepare maze
    // Khởi tạo maze với kích thước mong muốn, chọn điểm bắt đầu - kết thúc trong maze
    std::pair<int, int> shape = {15, 15};
    Maze maze(shape);
    std::pair<std::pair<int, int>, std::pair<int, int>> startEnd = maze.selectStartAndEnd();

    // Khởi tạo các đối tượng bắt đầu di chuyển
    int numberObject = 50;
    std::vector<Object> objects;
    for (int i = 0; i < numberObject; ++i)
    {
        Object object(startEnd.first);
        objects.push_back(object);
    }

    // 1. Prepare work on static maze 
    AStar astar;
    ACO aco;
    // Dùng AStar tìm đường tối ưu - hàm trả về lấy map
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, AStar::HashPairAStar> aStarPath = astar.solve_serial(maze, startEnd.first, startEnd.second).second;
    // Dùng ACO tìm pheromone map - hàm trả về lấy map
    std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, double, ACO::HashPairACO> acoMap = aco.solve_serial(maze, startEnd.first, startEnd.second).second;
    
    // 2.
    // Start main problem in dynamic maze
    


    return 0;
}
