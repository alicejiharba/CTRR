#include <iostream>
#include "Algo.h"
using namespace std;

// Giả sử bạn đã include pathfinding.cpp với findShortestPathMatrix, createPathNode, printPath, freePath

void testTask2() {
    cout << "============================\n";
    cout << "     TEST TASK 2 - A* 2D\n";
    cout << "============================\n\n";

    double adj[100][100];
    int coords[100][2];

    auto reset = [&](int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = 0;
    };

    // ------------------------------------
    // TEST 1: Simple straight line (0 → 1 → 2)
    // ------------------------------------
    cout << "TEST 1: Simple linear graph\n";

    int n = 3;
    reset(n);

    coords[0][0] = 0; coords[0][1] = 0;
    coords[1][0] = 1; coords[1][1] = 0;
    coords[2][0] = 2; coords[2][1] = 0;

    adj[0][1] = 1;
    adj[1][2] = 1;

    PathNode* p1 = findShortestPath2D(adj, coords, 0, 2, 1);
    printPath(p1);
    freePath(p1);

    cout << "\n";

    // ------------------------------------
    // TEST 2: Two different paths, one longer
    // ------------------------------------
    cout << "TEST 2: Two paths, one shorter\n";

    n = 4;
    reset(n);

    coords[0][0] = 0; coords[0][1] = 0;
    coords[1][0] = 1; coords[1][1] = 0;
    coords[2][0] = 0; coords[2][1] = 1;
    coords[3][0] = 1; coords[3][1] = 1;

    adj[0][1] = 1;
    adj[1][3] = 1;

    adj[0][2] = 5; // longer path
    adj[2][3] = 5;

    PathNode* p2 = findShortestPath2D(adj, coords, 0, 3, 1);
    printPath(p2);
    freePath(p2);

    cout << "\n";

    // ------------------------------------
    // TEST 3: No path
    // ------------------------------------
    cout << "TEST 3: No path\n";

    n = 3;
    reset(n);

    coords[0][0] = 0; coords[0][1] = 0;
    coords[1][0] = 1; coords[1][1] = 1;
    coords[2][0] = 2; coords[2][1] = 2;

    adj[0][1] = 0;
    adj[1][2] = 0;

    PathNode* p3 = findShortestPath2D(adj, coords, 0, 2, 1);
    printPath(p3);
    freePath(p3);

    cout << "\n";

    // ------------------------------------
    // TEST 4: Manhattan vs Euclidean comparison
    // ------------------------------------
    cout << "TEST 4: Manhattan vs Euclidean\n";

    n = 2;
    reset(n);

    coords[0][0] = 0; coords[0][1] = 0;
    coords[1][0] = 3; coords[1][1] = 4;  // distance = 5

    adj[0][1] = 5;

    cout << "Mode 1 (Manhattan):\n";
    PathNode* p4a = findShortestPath2D(adj, coords, 0, 1, 1);
    printPath(p4a);

    cout << "\nMode 2 (Euclidean):\n";
    PathNode* p4b = findShortestPath2D(adj, coords, 0, 1, 2);
    printPath(p4b);

    freePath(p4a);
    freePath(p4b);

    cout << "\n";

    // ------------------------------------
    // TEST 5: Full connected graph
    // ------------------------------------
    cout << "TEST 5: Complete graph\n";

    n = 4;
    reset(n);

    coords[0][0] = 0; coords[0][1] = 0;
    coords[1][0] = 1; coords[1][1] = 0;
    coords[2][0] = 0; coords[2][1] = 1;
    coords[3][0] = 1; coords[3][1] = 1;

    // fully connected with weight = distance
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                adj[i][j] = sqrt(
                    pow(coords[i][0] - coords[j][0], 2) +
                    pow(coords[i][1] - coords[j][1], 2)
                );

    PathNode* p5 = findShortestPath2D(adj, coords, 0, 3, 2);
    printPath(p5);
    freePath(p5);

    cout << "\n============================\n";
    cout << "     END OF TEST TASK 2\n";
    cout << "============================\n";
}
