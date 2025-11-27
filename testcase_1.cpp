#include <iostream>
#include "Algo.h"
using namespace std;

// Giả sử bạn đã include pathfinding.cpp với findShortestPathMatrix, createPathNode, printPath, freePath

void runTestCases_1() {
    double adjMatrix[100][100];

    // Test case 1: Simple linear 3-node graph: 0-1-2
    int n = 3;
    for(int i=0;i<n;i++) 
        for(int j=0;j<n;j++) 
            adjMatrix[i][j]=0;
    adjMatrix[0][1]=1; 
    adjMatrix[1][2]=1;
    // cout << "Matrix for Test 1:" << adjMatrix;
    cout << "Test 1 (0->2): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 2));

    // Test case 2: 4-node complete graph
    n=4;
    for(int i=0;i<n;i++) 
        for(int j=0;j<n;j++) adjMatrix[i][j]= (i!=j ? 1:0);
    cout << "Test 2 (0->3): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 3));

    // Test case 3: Graph with disconnected node
    n=4;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    adjMatrix[0][1]=1; adjMatrix[1][2]=1; // node 3 disconnected
    cout << "Test 3 (0->3, no path): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 3));

    // Test case 4: Graph with cycle
    n=4;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    adjMatrix[0][1]=1; adjMatrix[1][2]=1; adjMatrix[2][0]=1; adjMatrix[2][3]=1;
    cout << "Test 4 (0->3): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 3));

    // Test case 5: Start = goal
    n=3;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    adjMatrix[0][1]=1; adjMatrix[1][2]=1;
    cout << "Test 5 (1->1): ";
    printPath(findShortestPathMatrix(adjMatrix, 1, 1));

    // Test case 6: Two paths, one longer than other
    n=5;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    adjMatrix[0][1]=1; adjMatrix[1][4]=1; adjMatrix[0][2]=1; adjMatrix[2][3]=1; adjMatrix[3][4]=1;
    cout << "Test 6 (0->4): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 4));

    // Test case 7: Fully disconnected graph
    n=3;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    cout << "Test 7 (0->2, no path): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 2));

    // Test case 8: Star graph (0 connected to all)
    n=5;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    for(int i=0;i<n-1;i++) { 
        adjMatrix[i][i+1]=1; 
        adjMatrix[i+1][i]=1;
    }
    cout << "Test 8 (0->3): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 3));

    // Test case 9: Chain graph 0-1-2-3-4
    n=5;
    for(int i=0;i<n;i++) 
        for(int j=0;j<n;j++) 
            adjMatrix[i][j]=0;
    for(int i=0;i<n-1;i++) { 
        adjMatrix[i][i+1]=1; 
        adjMatrix[i+1][i]=1;
    }
    cout << "Test 9 (0->4): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 4));

    // Test case 10: Multiple equal length paths
    n=4;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) adjMatrix[i][j]=0;
    adjMatrix[0][1]=1; adjMatrix[1][3]=1; adjMatrix[0][2]=1; adjMatrix[2][3]=1;
    cout << "Test 10 (0->3): ";
    printPath(findShortestPathMatrix(adjMatrix, 0, 3));
}
