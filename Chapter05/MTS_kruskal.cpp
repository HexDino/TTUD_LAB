#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int find(int u, vector<int>& parent) {
    if (u != parent[u]) {
        parent[u] = find(parent[u], parent);
    }
    return parent[u];
}

void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = find(u, parent);
    v = find(v, parent);
    if (u != v) {
        if (rank[u] < rank[v]) {
            swap(u, v);
        }
        parent[v] = u;
        if (rank[u] == rank[v]) {
            rank[u]++;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(N + 1), rank(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    int mst_weight = 0;
    int edges_used = 0;

    for (const auto& edge : edges) {
        if (find(edge.u, parent) != find(edge.v, parent)) {
            unionSets(edge.u, edge.v, parent, rank);
            mst_weight += edge.w;
            edges_used++;
            if (edges_used == N - 1) {
                break;
            }
        }
    }

    cout << mst_weight << endl;

    return 0;
}