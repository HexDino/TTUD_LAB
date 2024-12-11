#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> duration(n + 1, 0);
    for(int i = 1; i <= n; ++i){
        cin >> duration[i];
    }    vector<vector<int>> adj(n + 1, vector<int>());
    vector<int> in_degree(n + 1, 0);

    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    queue<int> q;
    vector<long long> earliest_finish(n + 1, 0);
    for(int i = 1; i <= n; ++i){
        if(in_degree[i] == 0){
            q.push(i);
            earliest_finish[i] = duration[i];
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto &v : adj[u]){
            if(earliest_finish[v] < earliest_finish[u] + duration[v]){
                earliest_finish[v] = earliest_finish[u] + duration[v];
            }
            in_degree[v]--;
            if(in_degree[v] == 0){
                q.push(v);
            }
        }
    }
    long long project_completion_time = 0;
    for(int i = 1; i <= n; ++i){
        if(earliest_finish[i] > project_completion_time){
            project_completion_time = earliest_finish[i];
        }
    }

    cout << project_completion_time;
    return 0;
}
