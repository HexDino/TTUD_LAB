#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> bus_info(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> bus_info[i].first >> bus_info[i].second;
    }
    
    vector<vector<int>> adj(n + 1, vector<int>());
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<vector<pair<int, int>>> bus_graph(n + 1, vector<pair<int, int>>());
    
    vector<int> visited(n + 1, 0);
    int visit_counter = 1;
    
    for(int i = 1; i <= n; ++i){
        int C = bus_info[i].first;
        int D = bus_info[i].second;
        
        vector<int> current_level;
        current_level.push_back(i);
        visited[i] = visit_counter;
        
        for(int step = 0; step < D; ++step){
            vector<int> next_level;
            for(auto &u : current_level){
                for(auto &v : adj[u]){
                    if(visited[v] != visit_counter){
                        visited[v] = visit_counter;
                        next_level.push_back(v);
                        if(v != i){
                            bus_graph[i].emplace_back(v, C);
                        }
                    }
                }
            }
            if(next_level.empty()) break;
            current_level = move(next_level);
        }
        visit_counter++;
    }
    
    vector<ll> dist(n + 1, INF);
    dist[1] = 0;
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, std::greater<pair<ll, int>>> pq;
    pq.emplace(0, 1);
    
    while(!pq.empty()){
        auto [current_cost, u] = pq.top();
        pq.pop();
        
        if(u == n){
            break;
        }
        
        if(current_cost > dist[u]){
            continue;
        }
        
        for(auto &[v, cost] : bus_graph[u]){
            if(dist[v] > dist[u] + (ll)cost){
                dist[v] = dist[u] + (ll)cost;
                pq.emplace(dist[v], v);
            }
        }
    }
    
    cout << dist[n];
}
