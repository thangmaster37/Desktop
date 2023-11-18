#include "../stmaze/stmaze.cpp"
#include "../serial/AStar.cpp"
#include "../serial/ACO.cpp"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

int main()
{
    // Step 0: Build dynamic maze
    int row = 10;
    int col = 100;
    std::vector<std::vector<bool>> dymaze = createMaze(row, col, 0.1);
    std::pair<std::pair<int, int>, std::pair<int, int>> startEndPoint = selectStartAndEnd(dymaze);

    // Step 1: Chọn 1 khoảnh khắc của dymaze để tạo stmaze
    // Thực hiện giải thuật A* and ACO để tạo cơ sở chạy kết hợp trên dymaze ở Step 2.
    std::vector<std::vector<bool>> stmaze = dymaze;
    std::vector<std::pair<int, int>> optimizePathAStar = AStar(stmaze, startEndPoint.first, startEndPoint.second);
    std::vector<std::pair<int, int>> optimizePathACO = ACO(stmaze, startEndPoint.first, startEndPoint.second);

    printMaze(dymaze);
    std::cout << "Path by serial AStar:\n";
    for (const auto &point : optimizePathAStar)
    {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << std::endl
              << "Step: " << optimizePathAStar.size() << std::endl;

    std::cout << "Path by serial ACO:\n";
    for (const auto &point : optimizePathACO)
    {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << std::endl
              << "Step: " << optimizePathACO.size() << std::endl;
    return 0;
}
