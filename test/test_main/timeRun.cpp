#include "../serial_algorithm/AStar.cpp"
#include "../serial_algorithm/ACO.cpp"
#include "../data_structure/data_structure_with_matrix.cpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include <list>
#include <fstream> 

double resultAStar(std::vector<std::vector<bool>> &maze, int m, int n, std::pair<int, int> start, std::pair<int, int> end) {
    // Đo thời gian bắt đầu
    auto begin = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<int, int>> path_AStar = AStar(maze, m, n, start, end);
    
    // Đo thời gian kết thúc harito
    auto end_ = std::chrono::high_resolution_clock::now();

    // Tính thời gian chạy
    std::chrono::duration<double> duration = end_ - begin;
    double timeInSeconds = duration.count();

    return timeInSeconds;

}

double resultACO(std::vector<std::vector<bool>> &maze, int m, int n, std::pair<int, int> start, std::pair<int, int> end) {
    // Đo thời gian bắt đầu
    auto begin = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<int, int>> path_ACO = ACO(maze, m, n, start, end);
    
    // Đo thời gian kết thúc
    auto end_ = std::chrono::high_resolution_clock::now();

    // Tính thời gian chạy
    std::chrono::duration<double> duration = end_ - begin;
    double timeInSeconds = duration.count();

    return timeInSeconds;

}

void WriteListToFile(const std::vector<std::vector<double>>& data_compare, const std::string& filename) {
    std::ofstream file(filename);
    
    if (file.is_open()) {
        for (const auto& row : data_compare) {
            for (const auto& element : row) {
                file << element << " ";
            }
            file << std::endl;
        }
        
        file.close();
        std::cout << "Data written to file successfully." << std::endl;
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}

int main()
{
    std::vector<std::vector<double>> data_compare = {};
    double timeAStar, timeACO;
    int row_column[] = {100,500,1000,5000};
    for (int i = 0; i < 4; i++) {
        std::vector<std::vector<bool>> maze = createMaze(row_column[i], row_column[i], 0.3);
        std::pair<std::pair<int, int>, std::pair<int, int>> startAndEnd = selectStartAndEnd(maze);
        std::pair<int, int> start = startAndEnd.first;
        std::pair<int, int> end = startAndEnd.second;

        timeAStar = resultAStar(maze, row_column[i], row_column[i], start, end);
        timeACO = resultACO(maze, row_column[i], row_column[i], start, end);

        std::vector<double> arrays;

        arrays.push_back(timeAStar);
        arrays.push_back(timeACO);

        data_compare.push_back(arrays);

    }
    std::string filename = "../test_main/compareAlgorithm/data_compare_time.txt";
    WriteListToFile(data_compare, filename);

    return 0;
}