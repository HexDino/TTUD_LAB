#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

bool bpm(int u, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &matchR) {
    for (int v : graph[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (matchR[v] == -1 || bpm(matchR[v], graph, visited, matchR)) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxBipartiteMatching(int n, int m, vector<vector<int>> &graph) {
    vector<int> matchR(m + 1, -1);
    int result = 0;

    for (int u = 1; u <= n; ++u) {
        vector<bool> visited(m + 1, false);
        if (bpm(u, graph, visited, matchR)) {
            result++;
        }
    }

    return result;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int staff;
            cin >> staff;
            graph[i].push_back(staff);
        }
    }

    cout << maxBipartiteMatching(n, m, graph) << endl;

    return 0;
}
