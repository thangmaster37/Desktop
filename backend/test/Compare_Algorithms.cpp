#include "../algo/AStar.cpp"
#include "../algo/ACO.cpp"
#include "../Maze.cpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <list>
#include <fstream> 

#include <Windows.h>
#include <Psapi.h>
#include <functional>


class Compare_Algorithms {
    public:
        Maze maze;
        std::pair<int, int> start;
        std::pair<int, int> end;

        Compare_Algorithms() {}

        Compare_Algorithms(Maze &maze, std::pair<int, int> start, std::pair<int, int> end) {
            maze = maze;
            start = start;
            end = end;
        };
        
};

class Time_Algorithm: public Compare_Algorithms {
    public:
        Time_Algorithm() {}

        // double getTimeAlgorithmAStar(std::function<double()> functionCall) {
        //      // Đo thời gian bắt đầu
        //     auto begin_time = std::chrono::high_resolution_clock::now();

        //     auto path = functionCall();
            
        //     // Đo thời gian kết thúc
        //     auto end_time = std::chrono::high_resolution_clock::now();

        //     // Tính thời gian chạy
        //     std::chrono::duration<double> duration = end_time - begin_time;
        //     return duration.count();
        // }

        double getTimeAStarSerial() {
            // Đo thời gian bắt đầu
            auto begin_time = std::chrono::high_resolution_clock::now();

            auto path_AStar = AStar().solve_serial(maze, start, end);
            
            // Đo thời gian kết thúc
            auto end_time = std::chrono::high_resolution_clock::now();

            // Tính thời gian chạy
            std::chrono::duration<double> duration = end_time - begin_time;
            return duration.count();

        }

        double getTimeAStarParallel() {
            // Đo thời gian bắt đầu
            auto begin_time = std::chrono::high_resolution_clock::now();

            auto path_AStar = AStar().solve_parallel(maze, start, end);
            
            // Đo thời gian kết thúc
            auto end_time = std::chrono::high_resolution_clock::now();

            // Tính thời gian chạy
            std::chrono::duration<double> duration = end_time - begin_time;
            return duration.count();

        }

        double getTimeACOSerial() {
            // Đo thời gian bắt đầu
            auto begin_time = std::chrono::high_resolution_clock::now();

            auto path_ACO = ACO().solve_serial(maze, start, end);
            
            // Đo thời gian kết thúc
            auto end_time = std::chrono::high_resolution_clock::now();

            // Tính thời gian chạy
            std::chrono::duration<double> duration = end_time - begin_time;
            return duration.count();

        }

        double getTimeACOParallel() {
            // Đo thời gian bắt đầu
            auto begin_time = std::chrono::high_resolution_clock::now();

            auto path_ACO = ACO().solve_parallel(maze, start, end);
            
            // Đo thời gian kết thúc
            auto end_time = std::chrono::high_resolution_clock::now();

            // Tính thời gian chạy
            std::chrono::duration<double> duration = end_time - begin_time;
            return duration.count();

        }

};

class Memory_Algorithm: public Compare_Algorithms {
    public:

        Memory_Algorithm() {}

        #if defined(__linux__)
            // Linux
            #include <sys/sysinfo.h>

            unsigned long long getMemoryUsed() {
                struct sysinfo sysInfo;
                sysinfo(&sysInfo);
                unsigned long long memUsed = (sysInfo.totalram - sysInfo.freeram) * sysInfo.mem_unit;
                return memUsed;
            }

        #elif defined(_WIN32) || defined(_WIN64)
            // Windows
            #include <Windows.h>

            double getMemoryUsed() {
                HANDLE process = GetCurrentProcess();
                PROCESS_MEMORY_COUNTERS_EX pmc;
                if (GetProcessMemoryInfo(process, reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc))) {
                    SIZE_T usedRAM = pmc.WorkingSetSize;
                    double usedRAMInMB = static_cast<double>(usedRAM) / (1024 * 1024);
                    return usedRAMInMB;
                }
            }

           
        #elif defined(__APPLE__)
            // macOS
            #include <mach/mach.h>

            unsigned long long getMemoryUsed() {
                struct task_basic_info_64 info;
                mach_msg_type_number_t size = sizeof(info);
                task_info(mach_task_self(), TASK_BASIC_INFO_64, (task_info_t)&info, &size);
                unsigned long long memUsed = info.resident_size;
                return memUsed;
            }

        #else
            #error Unsupported operating system

        #endif

        double getMemoryAStarSerial() {

            auto path_AStar = AStar().solve_serial(maze, start, end);
            
            // Đo bộ nhớ đã sử dụng sau khi gọi hàm
            double memUsed = getMemoryUsed();

            return memUsed;
        }

        double getMemoryAStarParallel() {
    
            auto path_AStar = AStar().solve_parallel(maze, start, end);
            
            // Đo bộ nhớ đã sử dụng sau khi gọi hàm
            double memUsed = getMemoryUsed();

            return memUsed;
        }

        double getMemoryACOSerial() {

            auto path_ACO = ACO().solve_serial(maze, start, end);
            
            // Đo bộ nhớ đã sử dụng sau khi gọi hàm
            double memUsed = getMemoryUsed();

            return memUsed;
        }

        double getMemoryACOParallel() {

            auto path_ACO = ACO().solve_parallel(maze, start, end);
            
            // Đo bộ nhớ đã sử dụng sau khi gọi hàm
            double memUsed = getMemoryUsed();

            return memUsed;
        }
};

int main() {

    Maze myMaze = {
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false},
    };

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {7, 7};

    Compare_Algorithms compare(myMaze, start, end);
    Time_Algorithm time;
    time.maze = myMaze;
    time.start = start;
    time.end = end;
    
    std::cout << time.getTimeAStarSerial() << "s" << "\n";
    // std::cout << time.getTimeAStarParallel() << "\n";
    std::cout << time.getTimeACOSerial() << "s" << "\n";
    // std::cout << time.getTimeACOParallel() << "s" << std::endl;
    

    Memory_Algorithm memory;
    memory.maze = myMaze;
    memory.start = start;
    memory.end = end;

    std::cout << memory.getMemoryAStarSerial() << "MB" << std::endl;
    // std::cout << memory.getMemoryAStarParallel() << "MB" << std::endl;
    std::cout << memory.getMemoryACOSerial() << "MB" << std::endl;
    // std::cout << memory.getMemoryACOParallel() << "MB" << std::endl;

    return 0;
}