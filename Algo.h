#ifndef ALGO_H
#define ALGO_H

#include "PathNode.h"

// Task 1
PathNode* findShortestPathMatrix(double adjMatrix[100][100], int start, int goal);

// Task 2
PathNode* findShortestPath2D(double adjMatrix[100][100], int coords[100][2], int start, int goal, int mode);

// Task 3
PathNode* findPathInMaze(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY);

// Task 4
PathNode* findPathInMaze2(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY, double weightMatrix[100][100]);

#endif
