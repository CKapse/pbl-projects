/*
 * ============================================================
 *  MIT-WPU CAMPUS NAVIGATION SYSTEM
 *  Project Based Learning - II (Design and Analysis of Algorithms)
 *  MIT World Peace University, Pune
 *
 *  Algorithms: Dijkstra | Prim's | Kruskal's | BFS | DFS
 *  Graph Representations: Adjacency Matrix + Adjacency List
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <string>
#include <iomanip>

using namespace std;

const int INF = INT_MAX;

// MIT-WPU Campus Buildings (nodes)
vector<string> buildings = {
    "Main Gate",           // 0
    "Saraswati Building",  // 1  - School of Law
    "Agastya Building",    // 2  - Library
    "Chanakya Building",   // 3  - School of Business
    "Vyas Building",       // 4  - School of CSE
    "Jamadagni Building",  // 5  - School of Mechanical
    "Shriraj Building",    // 6  - Canteen
    "Vivekanand Building", // 7  - Auditorium
    "Dronacharya Building",// 8  - Sports Complex
    "World Peace Dome",    // 9  - Landmark / Peace Studies
    "Medical Center",      // 10 - Campus Health Facility
    "Boys Hostel"          // 11 - Residential Block
};

int V; // number of vertices

// ============================================================
//  GRAPH CLASS (Dual Representation)
// ============================================================

class Campus {
public:
    int n;
    vector<vector<int>> adjMatrix;
    vector<vector<pair<int,int>>> adjList;
    vector<tuple<int,int,int>> edgeList;

    Campus(int nodes) : n(nodes) {
        adjMatrix.assign(n, vector<int>(n, 0));
        adjList.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
        edgeList.push_back({w, u, v});
    }

    void printMatrix() {
        cout << "\n--- Adjacency Matrix (distances in meters) ---\n";
        cout << setw(22) << " ";
        for (int i = 0; i < n; i++)
            cout << setw(5) << i;
        cout << "\n";
        for (int i = 0; i < n; i++) {
            cout << setw(22) << buildings[i].substr(0, 20);
            for (int j = 0; j < n; j++)
                cout << setw(5) << adjMatrix[i][j];
            cout << "\n";
        }
    }

    void printList() {
        cout << "\n--- Adjacency List ---\n";
        for (int i = 0; i < n; i++) {
            cout << "[" << setw(2) << i << "] " << setw(22) << buildings[i] << " -> ";
            for (auto& [v, w] : adjList[i])
                cout << buildings[v] << "(" << w << "m)  ";
            cout << "\n";
        }
    }
};

// ============================================================
//  1. DIJKSTRA'S ALGORITHM
//     Adjacency List + Min-Heap
//     Time: O((V + E) log V)  |  Space: O(V)
// ============================================================

void dijkstra(Campus& g, int src, int dest) {
    cout << "\n============================================================\n";
    cout << " DIJKSTRA'S SHORTEST PATH\n";
    cout << " From : " << buildings[src] << "\n";
    cout << " To   : " << buildings[dest] << "\n";
    cout << "============================================================\n";

    vector<int> dist(g.n, INF);
    vector<int> parent(g.n, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : g.adjList[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest distances from " << buildings[src] << ":\n";
    for (int i = 0; i < g.n; i++) {
        cout << "  -> " << setw(22) << buildings[i] << ": ";
        if (dist[i] == INF) cout << "Unreachable\n";
        else cout << dist[i] << " m\n";
    }

    if (dist[dest] == INF) {
        cout << "\nNo path found to " << buildings[dest] << "\n";
        return;
    }

    cout << "\nOptimal path to " << buildings[dest] << " (" << dist[dest] << " m):\n  ";
    vector<int> path;
    for (int cur = dest; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        if (i) cout << " --> ";
        cout << buildings[path[i]];
    }
    cout << "\n";
}

// ============================================================
//  2. PRIM'S ALGORITHM (MST)
//     Adjacency Matrix
//     Time: O(V^2)  |  Space: O(V)
// ============================================================

void primsAlgorithm(Campus& g) {
    cout << "\n============================================================\n";
    cout << " PRIM'S ALGORITHM - MINIMUM SPANNING TREE\n";
    cout << "============================================================\n";

    vector<int> key(g.n, INF);
    vector<int> parent(g.n, -1);
    vector<bool> inMST(g.n, false);

    key[0] = 0;
    int totalCost = 0;

    for (int count = 0; count < g.n - 1; count++) {
        int u = -1;
        for (int v = 0; v < g.n; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        inMST[u] = true;

        for (int v = 0; v < g.n; v++) {
            if (g.adjMatrix[u][v] && !inMST[v] && g.adjMatrix[u][v] < key[v]) {
                key[v] = g.adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\nMST Edges (minimum cost to connect all MIT-WPU buildings):\n";
    cout << setw(24) << "From" << setw(24) << "To" << setw(12) << "Cost(m)\n";
    cout << string(60, '-') << "\n";
    for (int i = 1; i < g.n; i++) {
        if (parent[i] != -1) {
            cout << setw(24) << buildings[parent[i]]
                 << setw(24) << buildings[i]
                 << setw(12) << g.adjMatrix[i][parent[i]] << "\n";
            totalCost += g.adjMatrix[i][parent[i]];
        }
    }
    cout << string(60, '-') << "\n";
    cout << "  Total MST cost (Prim's): " << totalCost << " m\n";
}

// ============================================================
//  3. KRUSKAL'S ALGORITHM (MST)
//     Edge List + Union-Find (DSU)
//     Time: O(E log E)  |  Space: O(V)
// ============================================================

class DSU {
public:
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

void kruskalsAlgorithm(Campus& g) {
    cout << "\n============================================================\n";
    cout << " KRUSKAL'S ALGORITHM - MINIMUM SPANNING TREE\n";
    cout << "============================================================\n";

    vector<tuple<int,int,int>> edges = g.edgeList;
    sort(edges.begin(), edges.end());

    DSU dsu(g.n);
    int totalCost = 0, edgesAdded = 0;

    cout << "\nMST Edges (minimum cost to connect all MIT-WPU buildings):\n";
    cout << setw(24) << "From" << setw(24) << "To" << setw(12) << "Cost(m)\n";
    cout << string(60, '-') << "\n";

    for (auto& [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            cout << setw(24) << buildings[u]
                 << setw(24) << buildings[v]
                 << setw(12) << w << "\n";
            totalCost += w;
            edgesAdded++;
            if (edgesAdded == g.n - 1) break;
        }
    }
    cout << string(60, '-') << "\n";
    cout << "  Total MST cost (Kruskal's): " << totalCost << " m\n";
}

// ============================================================
//  4. BFS - Breadth First Search
//     Time: O(V + E)  |  Space: O(V)
// ============================================================

void bfs(Campus& g, int src) {
    cout << "\n============================================================\n";
    cout << " BFS TRAVERSAL from: " << buildings[src] << "\n";
    cout << "============================================================\n";

    vector<bool> visited(g.n, false);
    vector<int> distance(g.n, -1);
    queue<int> q;

    visited[src] = true;
    distance[src] = 0;
    q.push(src);

    cout << "\nLevel-order traversal:\n";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << "  [Level " << distance[u] << "] " << buildings[u] << "\n";
        for (auto& [v, w] : g.adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                distance[v] = distance[u] + 1;
                q.push(v);
            }
        }
    }

    cout << "\nHop distances from " << buildings[src] << ":\n";
    for (int i = 0; i < g.n; i++)
        cout << "  -> " << setw(22) << buildings[i] << ": "
             << (distance[i] == -1 ? "Unreachable" : to_string(distance[i]) + " hop(s)") << "\n";
}

// ============================================================
//  5. DFS - Depth First Search
//     Time: O(V + E)  |  Space: O(V)
// ============================================================

void dfsHelper(Campus& g, int u, vector<bool>& visited, int depth) {
    visited[u] = true;
    cout << string(depth * 2, ' ') << "-> " << buildings[u] << "\n";
    for (auto& [v, w] : g.adjList[u])
        if (!visited[v])
            dfsHelper(g, v, visited, depth + 1);
}

void dfs(Campus& g, int src) {
    cout << "\n============================================================\n";
    cout << " DFS TRAVERSAL from: " << buildings[src] << "\n";
    cout << "============================================================\n";

    vector<bool> visited(g.n, false);
    cout << "\nDepth-first traversal:\n";
    dfsHelper(g, src, visited, 0);
}

// ============================================================
//  COMPLEXITY SUMMARY
// ============================================================

void printComplexity() {
    cout << "\n============================================================\n";
    cout << " COMPLEXITY ANALYSIS SUMMARY\n";
    cout << "============================================================\n";
    cout << left;
    cout << setw(22) << "Algorithm"
         << setw(22) << "Time Complexity"
         << setw(14) << "Space"
         << "Notes\n";
    cout << string(80, '-') << "\n";
    cout << setw(22) << "Dijkstra (matrix)"   << setw(22) << "O(V^2)"           << setw(14) << "O(V)" << "Dense graphs\n";
    cout << setw(22) << "Dijkstra (list)"     << setw(22) << "O((V+E) log V)"   << setw(14) << "O(V)" << "Sparse graphs, uses min-heap\n";
    cout << setw(22) << "Prim's"              << setw(22) << "O(V^2)"           << setw(14) << "O(V)" << "Adjacency matrix\n";
    cout << setw(22) << "Kruskal's"           << setw(22) << "O(E log E)"       << setw(14) << "O(V)" << "Edge list + DSU\n";
    cout << setw(22) << "BFS"                 << setw(22) << "O(V + E)"         << setw(14) << "O(V)" << "Level-order, shortest hops\n";
    cout << setw(22) << "DFS"                 << setw(22) << "O(V + E)"         << setw(14) << "O(V)" << "Depth-first exploration\n";
    cout << string(80, '-') << "\n";
    cout << "V = " << buildings.size() << " buildings  |  E = number of campus paths\n";
    cout << "\nBest/Average/Worst Case:\n";
    cout << "  Dijkstra  : Best O(E), Avg O((V+E)logV), Worst O(V^2) with matrix\n";
    cout << "  Prim's    : Best O(V^2), Avg O(V^2), Worst O(V^2) - adj matrix\n";
    cout << "  Kruskal's : Best O(E), Avg O(E logE), Worst O(E logE)\n";
    cout << "  BFS/DFS   : O(V+E) in all cases\n";
}

// ============================================================
//  MAIN - MENU DRIVEN
// ============================================================

int main() {
    V = buildings.size(); // 12 nodes
    Campus campus(V);

    // MIT-WPU campus path edges (u, v, distance_in_meters)
    // Estimated based on a 65-acre campus layout
    campus.addEdge(0, 1, 100);   // Main Gate -> Saraswati (Law) - near gate
    campus.addEdge(0, 9, 180);   // Main Gate -> World Peace Dome - central
    campus.addEdge(1, 2, 120);   // Saraswati -> Agastya (Library)
    campus.addEdge(1, 3, 150);   // Saraswati -> Chanakya (Business)
    campus.addEdge(2, 4, 90);    // Agastya (Library) -> Vyas (CSE)
    campus.addEdge(2, 7, 140);   // Agastya (Library) -> Vivekanand (Auditorium)
    campus.addEdge(3, 4, 110);   // Chanakya (Business) -> Vyas (CSE)
    campus.addEdge(3, 9, 130);   // Chanakya -> World Peace Dome
    campus.addEdge(4, 5, 160);   // Vyas (CSE) -> Jamadagni (Mechanical)
    campus.addEdge(4, 6, 80);    // Vyas (CSE) -> Shriraj (Canteen) - students go often
    campus.addEdge(5, 8, 200);   // Jamadagni (Mech) -> Dronacharya (Sports)
    campus.addEdge(5, 6, 120);   // Jamadagni -> Shriraj (Canteen)
    campus.addEdge(6, 10, 150);  // Shriraj (Canteen) -> Medical Center
    campus.addEdge(6, 11, 220);  // Shriraj (Canteen) -> Boys Hostel
    campus.addEdge(7, 9, 110);   // Vivekanand (Auditorium) -> World Peace Dome
    campus.addEdge(8, 11, 180);  // Dronacharya (Sports) -> Boys Hostel
    campus.addEdge(9, 10, 160);  // World Peace Dome -> Medical Center
    campus.addEdge(10, 11, 130); // Medical Center -> Boys Hostel

    cout << "============================================================\n";
    cout << "    MIT-WPU CAMPUS NAVIGATION SYSTEM\n";
    cout << "    MIT World Peace University, Pune\n";
    cout << "    Design and Analysis of Algorithms - Mini Project\n";
    cout << "============================================================\n";

    cout << "\nCampus Buildings:\n";
    for (int i = 0; i < V; i++)
        cout << "  [" << setw(2) << i << "] " << buildings[i] << "\n";

    campus.printMatrix();
    campus.printList();

    int choice;
    do {
        cout << "\n============================================================\n";
        cout << " MAIN MENU\n";
        cout << "============================================================\n";
        cout << "  1. Find Shortest Path        (Dijkstra's Algorithm)\n";
        cout << "  2. Minimum Spanning Tree     (Prim's Algorithm)\n";
        cout << "  3. Minimum Spanning Tree     (Kruskal's Algorithm)\n";
        cout << "  4. BFS Traversal\n";
        cout << "  5. DFS Traversal\n";
        cout << "  6. Complexity Analysis\n";
        cout << "  0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int src, dest;
                cout << "Enter source building (0-" << V-1 << "): "; cin >> src;
                cout << "Enter destination building (0-" << V-1 << "): "; cin >> dest;
                dijkstra(campus, src, dest);
                break;
            }
            case 2: primsAlgorithm(campus); break;
            case 3: kruskalsAlgorithm(campus); break;
            case 4: {
                int src;
                cout << "Enter source building (0-" << V-1 << "): "; cin >> src;
                bfs(campus, src);
                break;
            }
            case 5: {
                int src;
                cout << "Enter source building (0-" << V-1 << "): "; cin >> src;
                dfs(campus, src);
                break;
            }
            case 6: printComplexity(); break;
            case 0: cout << "\nThank you! - MIT-WPU Navigation System\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
