// #include <iostream>
// #include <random>

// using namespace std;

// // Hàm tạo mê cung
// bool **createMaze(int n, int m)
// {
//     // Khởi tạo mê cung. Quy ước:
//     // false: 0 - không bị chặn
//     // true: 1 - bị chặn
//     // vì mê cung được chủ động thiết kế để có nhiều đường đi - tức ít bị chặn - tức nhiều ô giá trị 0
//     // nhờ nhiều ô giá trị 0 - tức transistor ở trạng thái tắt nhiều hơn
//     // -> Tiết kiệm điện hơn

//     // Cách biểu diễn 1: Sử dụng con trỏ tối ưu lưu trữ
//     bool **maze = new bool *[n];

//     for (int i = 0; i < n; i++)
//     {
//         maze[i] = new bool[m];
//         for (int j = 0; j < m; j++)
//         {
//             maze[i][j] = false;
//         }
//     }

//     // Tạo các bức tường
//     for (int i = 0; i < n; i++)
//     {
//         maze[i][0] = true;
//         maze[i][m - 1] = true;
//     }
//     for (int j = 0; j < m; j++)
//     {
//         maze[0][j] = true;
//         maze[n - 1][j] = true;
//     }

//     // Tạo các lối đi
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<> dis(0, n - 1);
//     uniform_int_distribution<> dis2(0, m - 1);
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
//             {
//                 continue;
//             }
//             if (rand() % 2 == 0)
//             {
//                 maze[i][j] = true;
//             }
//         }
//     }

//     // Tạo đường vào và ra mê cung
//     maze[0][0] = true;
//     maze[n - 1][m - 1] = true;

//     return maze;
// }

// // Hàm in mê cung
// void printMaze(bool **maze, int n, int m)
// {
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (maze[i][j])
//             {
//                 cout << " ";
//             }
//             else
//             {
//                 cout << "*";
//             }
//         }
//         cout << endl;
//     }
// }

// int main()
// {
//     // Tạo mê cung
//     int n = 10;
//     int m = 10;
//     bool **maze = createMaze(n, m);

//     // In mê cung
//     printMaze(maze, n, m);

//     // Giải phóng bộ nhớ
//     for (int i = 0; i < n; i++)
//     {
//         delete[] maze[i];
//     }
//     delete[] maze;

//     return 0;
// }
