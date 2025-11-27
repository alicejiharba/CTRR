#include "Algo.h"

// TODO: Implement các hàm theo đề yêu cầu
PathNode* findShortestPathMatrix(double adjMatrix[100][100], int start, int goal) {
    int nVertices = 100;

    for (int i = 99; i >= 0; i--) {
        bool nonZero = false;
        for (int j = 0; j < 100; j++) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                nonZero = true;
                break;
            }
        }
        if (nonZero) {
            nVertices = i + 1;
            break;
        }
    }

    if (start < 0 || start >= nVertices || goal < 0 || goal >= nVertices)
        return nullptr;

    auto calcHeuristic = [&](int src) {
        if (src == goal) return 0;

        int dist[100];
        for (int i = 0; i < nVertices; i++) dist[i] = -1;

        int q[1000];
        int head = 0, tail = 0;
        q[tail++] = src;
        dist[src] = 0;

        while (head < tail) {
            int v = q[head++];
            for (int nb = 0; nb < nVertices; nb++) {
                if (adjMatrix[v][nb] != 0 && dist[nb] == -1) {
                    dist[nb] = dist[v] + 1;
                    if (nb == goal) return dist[nb];
                    q[tail++] = nb;
                }
            }
        }
        return 1000000;
    };

    double h[100];
    for (int i = 0; i < nVertices; i++)
        h[i] = calcHeuristic(i);

    double g[100], f[100];
    bool closed[100] = {false};
    int parent[100];

    for (int i = 0; i < nVertices; i++) {
        g[i] = 1e18;
        f[i] = 1e18;
        parent[i] = -1;
    }

    g[start] = 0;
    f[start] = h[start];

    struct Item {
        double f, g, h;
        int idx;
    };

    struct Cmp {
        bool operator()(const Item &a, const Item &b) const {
            if (a.f != b.f) return a.f < b.f;
    
            if (a.h != b.h) return a.h < b.h;
    
            return a.idx < b.idx;
        }
    };


    vector<Item> pq;

    auto pushPQ = [&](Item it) {
        pq.push_back(it);
        sort(pq.begin(), pq.end(), Cmp());
    };

    auto popPQ = [&]() {
        pq.erase(pq.begin());
    };

    auto topPQ = [&]() {
        return pq.front();
    };

    pushPQ({f[start], g[start], h[start], start});


    while (!pq.empty()) {

        Item t = topPQ();
        popPQ();

        double curF = t.f;
        double curG = t.g;
        int current = t.idx;

        if (closed[current]) continue;
        if (curF != f[current] || curG != g[current]) continue;

        if (current == goal) {
            PathNode *headNode = nullptr;
            int v = goal;
            while (v != -1) {
                PathNode *node = createPathNode(to_string(v), f[v], g[v], h[v]);
                node->next = headNode;
                headNode = node;
                v = parent[v];
            }
            return headNode;
        }

        closed[current] = true;

        for (int nb = 0; nb < nVertices; nb++) {
            if (adjMatrix[current][nb] == 0) continue;
            if (closed[nb]) continue;

            double tentative = g[current] + 1;

            bool better = false;
            if (tentative < g[nb]) better = true;
            else if (tentative == g[nb] && current < parent[nb]) better = true;

            if (better) {
                parent[nb] = current;
                g[nb] = tentative;
                f[nb] = g[nb] + h[nb];
                pushPQ({f[nb], g[nb], h[nb], nb});;
            }
        }
    }

    return nullptr;
}

PathNode* findShortestPath2D(double adjMatrix[100][100], int coords[100][2], int start, int goal, int mode) {
    // Viết code A* cho không gian 2D với mode heuristic
    // 1. Xác định số đỉnh thực tế
    int nVertices = 100;
    for (int i = 99; i >= 0; i--) {
        bool nonZero = false;
        for (int j = 0; j < 100; j++) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                nonZero = true;
                break;
            }
        }
        if (nonZero) {
            nVertices = i + 1;
            break;
        }
    }

    if (start < 0 || start >= nVertices || goal < 0 || goal >= nVertices)
        return nullptr;

    // ================================
    // 2. Heuristic function
    // ================================
    auto heuristic = [&](int v) {
        int x1 = coords[v][0], y1 = coords[v][1];
        int x2 = coords[goal][0], y2 = coords[goal][1];

        if (mode == 1) {
            // Manhattan
            return (double)(abs(x1 - x2) + abs(y1 - y2));
        } else {
            // Euclidean
            double dx = x1 - x2;
            double dy = y1 - y2;
            return sqrt(dx * dx + dy * dy);
        }
    };

    // ================================
    // 3. A* setup
    // ================================
    double g[100], h[100], f[100];
    bool inOpen[100] = {false};
    bool closed[100] = {false};
    int parent[100];

    for (int i = 0; i < nVertices; i++) {
        g[i] = 1e18;
        f[i] = 1e18;
        parent[i] = -1;
    }

    // Tính heuristic cho tất cả nodes
    for (int i = 0; i < nVertices; i++)
        h[i] = heuristic(i);

    g[start] = 0;
    f[start] = h[start];
    inOpen[start] = true;

    // ================================
    // 4. A* main loop
    // ================================
    while (true) {
        // Tìm node trong open có f nhỏ nhất
        int current = -1;
        double bestF = 1e18;

        for (int i = 0; i < nVertices; i++) {
            if (inOpen[i] && !closed[i] && f[i] < bestF) {
                bestF = f[i];
                current = i;
            }
        }

        if (current == -1)
            return nullptr; // không còn node → không có đường đi

        if (current == goal) {
            // ================================
            // 5. Reconstruct path -> Linked List
            // ================================
            PathNode* head = nullptr;
            int v = goal;

            while (v != -1) {
                std::string name = "(" + std::to_string(coords[v][0]) +
                                   ", " + std::to_string(coords[v][1]) + ")";
                PathNode* newNode = createPathNode(name, f[v], g[v], h[v]);
                newNode->next = head;
                head = newNode;
                v = parent[v];
            }

            return head;
        }

        inOpen[current] = false;
        closed[current] = true;

        // Duyệt các neighbor
        for (int nb = 0; nb < nVertices; nb++) {
            if (adjMatrix[current][nb] == 0)
                continue;

            if (closed[nb])
                continue;

            double weight = adjMatrix[current][nb];
            double tentative_g = g[current] + weight;

            if (!inOpen[nb] || tentative_g < g[nb]) {
                parent[nb] = current;
                g[nb] = tentative_g;
                f[nb] = g[nb] + h[nb];
                inOpen[nb] = true;
            }
        }
    }

    return nullptr;
}

PathNode* findPathInMaze(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY) {
    auto inBounds = [&](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0;
    };

    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1,  1, -1, 1};
    string dirName[8] = {
        "Up", "Down", "Left", "Right",
        "Up-Left", "Up-Right", "Down-Left", "Down-Right"
    };

    double moveCost[8] = {1, 1, 1, 1, 1.5, 1.5, 1.5, 1.5};

    auto idx = [&](int x, int y) {
        return x * n + y;
    };
    auto coordX = [&](int id) { return id / n; };
    auto coordY = [&](int id) { return id % n; };

    int start = idx(startX, startY);
    int goal  = idx(goalX, goalY);
    int totalNodes = m * n;

    auto heuristic = [&](int id) {
        int x = coordX(id), y = coordY(id);
        return (double)(abs(x - goalX) + abs(y - goalY));
    };

    double g[10000], h[10000], f[10000];
    bool inOpen[10000] = {false};
    bool closed[10000] = {false};
    int parent[10000];
    int moveDir[10000];

    for (int i = 0; i < totalNodes; i++) {
        g[i] = 1e18;
        f[i] = 1e18;
        parent[i] = -1;
        moveDir[i] = -1;
        h[i] = heuristic(i);
    }

    g[start] = 0;
    f[start] = h[start];
    inOpen[start] = true;

    while (true) {
        int current = -1;
        double bestF = 1e18;

        for (int i = 0; i < totalNodes; i++) {
            if (inOpen[i] && !closed[i] && f[i] < bestF) {
                bestF = f[i];
                current = i;
            }
        }

        if (current == -1)
            return nullptr;

        if (current == goal) {
            PathNode* head = nullptr;
            int v = goal;

            while (v != -1) {
                string name = "";
                if (v != start) {
                    int d = moveDir[v];
                    string name = dirName[d];
            
                    PathNode* node = createPathNode(name, f[v], g[v], h[v]);
                    node->next = head;
                    head = node;
                }
                v = parent[v];
            }

            return head;
        }

        inOpen[current] = false;
        closed[current] = true;

        int cx = coordX(current), cy = coordY(current);

        for (int d = 0; d < 8; d++) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (!inBounds(nx, ny))
                continue;

            int nb = idx(nx, ny);
            if (closed[nb])
                continue;

            double tentative_g = g[current] + moveCost[d];

            if (!inOpen[nb] || tentative_g < g[nb]) {
                parent[nb] = current;
                moveDir[nb] = d;
                g[nb] = tentative_g;
                f[nb] = g[nb] + h[nb];
                inOpen[nb] = true;
            }
        }
    }

    return nullptr;
}

PathNode* findPathInMaze2(int maze[100][100], int m, int n, 
                          int startX, int startY, int goalX, int goalY,
                          double weightMatrix[100][100]) 
{
    auto idx = [&](int x, int y){ return x*n + y; };
    auto cx = [&](int id){ return id/n; };
    auto cy = [&](int id){ return id%n; };

    // ================================
    // 1. Build weight matrix
    // ================================
    int dx[8] = {-1,1,0,0,-1,-1,1,1};
    int dy[8] = {0,0,-1,1,-1,1,-1,1};
    double baseCost[8] = {1,1,1,1,1.5,1.5,1.5,1.5};
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int u = i*n+j;
            for(int d=0; d<8; d++){
                int ni = i+dx[d], nj=j+dy[d];
                if(ni<0||ni>=m||nj<0||nj>=n) continue;
                if(maze[i][j]==1 || maze[ni][nj]==1) continue;
                int v = ni*n + nj;
                weightMatrix[u][v] = baseCost[d];
            }
        }
    }

    // ================================
    // 2. Setup A*
    // ================================
    int totalNodes = m * n;
    double g[10000], h[10000], f[10000];
    bool inOpen[10000] = {false};
    bool closed[10000] = {false};
    int parent[10000];

    for(int i = 0; i < totalNodes; i++){
        g[i] = 1e18;
        f[i] = 1e18;
        parent[i] = -1;
        int x = cx(i), y = cy(i);
        h[i] = abs(x - goalX) + abs(y - goalY); // Manhattan
    }

    int start = idx(startX,startY);
    int goal  = idx(goalX,goalY);

    g[start] = 0;
    f[start] = h[start];
    inOpen[start] = true;

    // ================================
    // 3. A* Main loop
    // ================================
    while(true){
        int current = -1;
        double bestF = 1e18;
        for(int i = 0; i < totalNodes; i++){
            if(inOpen[i] && !closed[i] && f[i] < bestF){
                bestF = f[i];
                current = i;
            }
        }

        if(current == -1) return nullptr;
        if(current == goal) break;

        inOpen[current] = false;
        closed[current] = true;

        int x = cx(current), y = cy(current);
        for(int d = 0; d < 8; d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx<0 || nx>=m || ny<0 || ny>=n) continue;
            if(maze[nx][ny]==1) continue;

            int nb = idx(nx,ny);
            if(closed[nb]) continue;

            double tentative_g = g[current] + baseCost[d];
            if(!inOpen[nb] || tentative_g < g[nb]){
                g[nb] = tentative_g;
                f[nb] = g[nb] + h[nb];
                parent[nb] = current;
                inOpen[nb] = true;
            }
        }
    }

    // ================================
    // 4. Reconstruct path (bao gồm start)
    // ================================
    PathNode* head = nullptr;
    int v = goal;
    while(v != -1){
        int x = cx(v), y = cy(v);
        string name = "(" + to_string(x) + ", " + to_string(y) + ")";
        PathNode* node = createPathNode(name, f[v], g[v], h[v]);
        node->next = head;
        head = node;
        v = parent[v];
    }

    return head;
}

