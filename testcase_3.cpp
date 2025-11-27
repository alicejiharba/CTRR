#include <iostream>
#include "Algo.h"
using namespace std;

// Giả sử bạn đã include pathfinding.cpp với findShortestPathMatrix, createPathNode, printPath, freePath

void testTask3() {
    cout << "============================\n";
    cout << "       TEST TASK 3\n";
    cout << "============================\n\n";

    int maze[100][100];

    auto reset = [&](int m, int n) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                maze[i][j] = 0;
    };

    // ------------------------------------
    // TEST 1: Simple 2×3 maze (chỉ đi thẳng)
    // ------------------------------------
    cout << "TEST 1: Simple maze (straight path)\n";

    int m = 2, n = 3;
    reset(m, n);

    // 0 0 0
    // 0 0 0
    PathNode* p1 = findPathInMaze(maze, m, n, 0, 0, 0, 2);
    printPath(p1);
    freePath(p1);

    cout << "\n";

    // ------------------------------------
    // TEST 2: Maze có tường, buộc phải đi vòng
    // ------------------------------------
    cout << "TEST 2: Maze with walls\n";

    m = 3; n = 3;
    reset(m, n);

    maze[0][1] = 1;  // tường block đường thẳng
    maze[1][1] = 1;

    // Maze:
    // 0 1 0
    // 0 1 0
    // 0 0 0

    PathNode* p2 = findPathInMaze(maze, m, n, 0, 0, 2, 2);
    printPath(p2);
    freePath(p2);

    cout << "\n";

    // ------------------------------------
    // TEST 3: Bắt buộc phải đi đường chéo
    // ------------------------------------
    cout << "TEST 3: Diagonal path required\n";

    m = 3; n = 3;
    reset(m, n);

    maze[1][0] = 1;  // chặn đi thẳng xuống
    maze[0][1] = 1;  // chặn đi thẳng qua phải

    // Maze:
    // 0 1 0
    // 1 0 0
    // 0 0 0
    // đường duy nhất là (0,0) → (1,1) (chéo)

    PathNode* p3 = findPathInMaze(maze, m, n, 0, 0, 2, 2);
    printPath(p3);
    freePath(p3);

    cout << "\n";

    // ------------------------------------
    // TEST 4: No path
    // ------------------------------------
    cout << "TEST 4: No path\n";

    m = 3; n = 3;
    reset(m, n);

    maze[0][1] = 1;
    maze[1][0] = 1;
    maze[1][2] = 1;
    maze[2][1] = 1;

    // Maze:
    // 0 1 0
    // 1 0 1
    // 0 1 0
    // goal (2,2) bị cô lập

    PathNode* p4 = findPathInMaze(maze, m, n, 0, 0, 2, 2);
    printPath(p4);
    freePath(p4);

    cout << "\n";

    // ------------------------------------
    // TEST 5: Start = Goal
    // ------------------------------------
    cout << "TEST 5: Start = Goal\n";

    m = 3; n = 3;
    reset(m, n);

    PathNode* p5 = findPathInMaze(maze, m, n, 1, 1, 1, 1);
    printPath(p5);
    freePath(p5);

    cout << "\n";

    // ------------------------------------
    // TEST 6: Large open maze (performance + correctness)
    // ------------------------------------
    cout << "TEST 6: Large open maze (5x5)\n";

    m = 5; n = 5;
    reset(m, n);

    PathNode* p6 = findPathInMaze(maze, m, n, 0, 0, 4, 4);
    printPath(p6);
    freePath(p6);

    cout << "\n============================\n";
    cout << "     END OF TEST TASK 3\n";
    cout << "============================\n";
}
