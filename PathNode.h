#ifndef PATHNODE_H
#define PATHNODE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct PathNode {
    string name;
    double f;
    double g;
    double h;
    PathNode* next;
};

PathNode* createPathNode(const string& name, double f, double g, double h);
void printPath(PathNode* head);
void freePath(PathNode* head);

#endif
