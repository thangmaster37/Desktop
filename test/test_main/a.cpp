#include <iostream>
#include <fstream>
#include <vector>

void WriteListToFile(const std::vector<std::vector<int>>& list, const std::string& filename) {
    std::ofstream file(filename);
    
    if (file.is_open()) {
        for (const auto& row : list) {
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

int main() {
    std::vector<std::vector<int>> list = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    std::string filename = "../test_main/compareAlgorithm/data_compare.txt";
    
    WriteListToFile(list, filename);
    std::cout << list.at(1).at(1) <<std::endl;
    
    return 0;
}