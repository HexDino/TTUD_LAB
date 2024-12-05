#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> tree;
vector<bool> visited;
int max_distance, farthest_node;

void dfs(int node, int distance) {
    visited[node] = true;
    if (distance > max_distance) {
        max_distance = distance;
        farthest_node = node;
    }
    for (auto &edge : tree[node]) {
        int next_node = edge.first;
        int weight = edge.second;
        if (!visited[next_node]) {
            dfs(next_node, distance + weight);
        }
    }
}

int main() {
    int N;
    cin >> N;
    tree.resize(N + 1);
    visited.resize(N + 1, false);

    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    max_distance = 0;
    dfs(1, 0);

    fill(visited.begin(), visited.end(), false);
    max_distance = 0;
    dfs(farthest_node, 0);

    cout << max_distance << endl;

    return 0;
}