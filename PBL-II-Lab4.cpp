#include <iostream>

using namespace std;

const int n = 6; 
const int INF = 999999;

int prims(int start_v, int cost[n][n]) {
    int nearest[n];
    int t[n][3]; 
    int mincost = 0;
    int r = 0;

    nearest[start_v] = -1; 
    for (int i = 1; i < n; i++) {
        if (i != start_v) {
            nearest[i] = start_v;
        }
    }

    for (int i = 1; i < n - 1; i++) {
        int min = INF;
        int j = -1;

        for (int k = 1; k < n; k++) {
            if (nearest[k] != -1 && cost[k][nearest[k]] < min) {
                j = k;
                min = cost[k][nearest[k]];
            }
        }

        t[r][0] = nearest[j];
        t[r][1] = j;
        t[r][2] = min;
        r = r + 1;

        mincost = mincost + cost[j][nearest[j]];
        nearest[j] = -1;

        for (int k = 1; k < n; k++) {
            if (nearest[k] != -1 && (cost[k][nearest[k]] > cost[k][j])) {
                nearest[k] = j;
            }
        }
    }

    cout << "Edges in MST (t array):" << endl;
    for (int i = 0; i < r; i++) {
        cout << t[i][0] << " - " << t[i][1] << " (Cost: " << t[i][2] << ")" << endl;
    }

    return mincost;
}

int main() {
    int cost[n][n] = {
        {0,   0,   0,   0,   0,   0}, 
        {0, INF,   8,   4,  10, INF}, 
        {0,   8, INF,   9, INF,   5},
        {0,   4,   9, INF,  12,   6}, 
        {0,  10, INF,  12, INF,   7}, 
        {0, INF,   5,   6,   7, INF}  
    };

    int total_cost = prims(1, cost);
    cout << "\nTotal mincost: " << total_cost << endl;

    return 0;
}