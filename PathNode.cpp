#include "PathNode.h"

PathNode* createPathNode(const string& name, double f, double g, double h) {
    PathNode* node = new PathNode{name, f, g, h, nullptr};
    return node;
}

void printPath(PathNode* head) {
    cout << "Printing path:\n";
    PathNode* curr = head;
    while (curr) {
        cout << curr->name << " (f: " << curr->f
                  << ", g: " << curr->g << ", h: " << curr->h << ")\n";
        curr = curr->next;
    }
}

void freePath(PathNode* head) {
    while (head) {
        PathNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}
