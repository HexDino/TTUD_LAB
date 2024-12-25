#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring>

using namespace std;

const int INF = numeric_limits<int>::max();

bool bfs(int s, int t, vector<vector<int>> &capacity, vector<vector<int>> &adj, vector<int> &parent) {
    fill(parent.begin(), parent.end(), -1);
    queue<int> q;
    q.push(s);
    parent[s] = s;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int edmondsKarp(int n, int s, int t, vector<vector<int>> &capacity, vector<vector<int>> &adj) {
    int maxFlow = 0;
    vector<int> parent(n + 1);

    while (bfs(s, t, capacity, adj, parent)) {
        int flow = INF;
        int cur = t;

        while (cur != s) {
            int prev = parent[cur];
            flow = min(flow, capacity[prev][cur]);
            cur = prev;
        }

        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= flow;
            capacity[cur][prev] += flow;
            cur = prev;
        }

        maxFlow += flow;
    }

    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> adj(n + 1);

    int s, t;
    cin >> s >> t;

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << edmondsKarp(n, s, t, capacity, adj) << endl;

    return 0;
}
