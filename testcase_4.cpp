#include <iostream>
#include "Algo.h"
using namespace std;

// Giả sử bạn đã include pathfinding.cpp với findShortestPathMatrix, createPathNode, printPath, freePath

void testTask4() {
    cout << "============================\n";
    cout << "       TEST TASK 4\n";
    cout << "============================\n\n";

    int maze[100][100];
    double weight[100][100];

    auto reset = [&](int m, int n, double w) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                maze[i][j] = 0;
                weight[i][j] = w;  // assign equal weight
            }
    };

    // ----------------------------------------
    // TEST 1: Simple straight path, uniform weight
    // ----------------------------------------
    cout << "TEST 1: Simple uniform weight\n";

    int m = 2, n = 3;
    reset(m, n, 1.0);  // mỗi ô cost = 1

    PathNode* t1 = findPathInMaze2(maze, m, n, 0, 0, 0, 2, weight);
    printPath(t1);
    freePath(t1);

    cout << "\n";

    // ----------------------------------------
    // TEST 2: Walls force a diagonal path
    // ----------------------------------------
    cout << "TEST 2: Walls forcing diagonal\n";

    m = 3; n = 3;
    reset(m, n, 1.0);

    maze[0][1] = 1;
    maze[1][0] = 1;

    // Maze:
    // 0 1 0
    // 1 0 0
    // 0 0 0

    PathNode* t2 = findPathInMaze2(maze, m, n, 0, 0, 2, 2, weight);
    printPath(t2);
    freePath(t2);

    cout << "\n";

    // ----------------------------------------
    // TEST 3: Weighted path – A* phải né ô nặng
    // ----------------------------------------
    cout << "TEST 3: Avoid heavy-weight cells\n";

    m = 3; n = 3;
    reset(m, n, 1.0);

    weight[0][1] = 20;  // cost cực lớn
    weight[1][1] = 20;  // ô nặng → A* phải tránh

    // Maze:
    // 0 0 0
    // 0 0 0
    // 0 0 0
    //
    // Weight:
    // 1 20 1
    // 1 20 1
    // 1  1 1

    PathNode* t3 = findPathInMaze2(maze, m, n, 0, 0, 2, 2, weight);
    printPath(t3);
    freePath(t3);

    cout << "\n";

    // ----------------------------------------
    // TEST 4: No path
    // ----------------------------------------
    cout << "TEST 4: No path\n";

    m = 3; n = 3;
    reset(m, n, 1.0);

    maze[0][1] = 1;
    maze[1][0] = 1;
    maze[1][2] = 1;
    maze[2][1] = 1;

    // Goal quá bị chặn

    PathNode* t4 = findPathInMaze2(maze, m, n, 0, 0, 2, 2, weight);
    printPath(t4);
    freePath(t4);

    cout << "\n";

    // ----------------------------------------
    // TEST 5: Start = Goal
    // ----------------------------------------
    cout << "TEST 5: Start = Goal\n";

    m = 3; n = 3;
    reset(m, n, 1.0);

    PathNode* t5 = findPathInMaze2(maze, m, n, 1, 1, 1, 1, weight);
    printPath(t5);
    freePath(t5);

    cout << "\n";

    // ----------------------------------------
    // TEST 6: Larger maze with varied weight
    // ----------------------------------------
    cout << "TEST 6: Large weighted maze (5x5)\n";

    m = 5; n = 5;

    reset(m, n, 1.0);

    // tạo vùng nặng
    weight[2][1] = 10;
    weight[2][2] = 10;
    weight[2][3] = 10;

    // A* sẽ chọn đi vòng tránh hàng giữa

    PathNode* t6 = findPathInMaze2(maze, m, n, 0, 0, 4, 4, weight);
    printPath(t6);
    freePath(t6);

    cout << "\n============================\n";
    cout << "     END OF TEST TASK 4\n";
    cout << "============================\n";
}
