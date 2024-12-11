#include <bits/stdc++.h>
using namespace std;

int N,M;
vector<int> g[1000001];
int disc[1000001],low[1000001],timeD;
bool vis[1000001];
bool ap[1000001];
int parent[1000001];
int articulationCount,bridgeCount;

vector<pair<int,int>> bridges;

void dfs(int u) {
    vis[u] = true;
    disc[u] = low[u] = ++timeD;
    int child=0;
    for(auto &nx: g[u]){
        if(!vis[nx]){
            parent[nx]=u;
            child++;
            dfs(nx);
            low[u]=min(low[u],low[nx]);
            if(parent[u]==-1 && child>1) ap[u]=true;
            if(parent[u]!=-1 && low[nx]>=disc[u]) ap[u]=true;
            if(low[nx]>disc[u]) {
                bridgeCount++;
            }
        }
        else if(nx!=parent[u]) {
            low[u]=min(low[u],disc[nx]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>M;
    for(int i=0;i<M;i++){
        int X,Y; cin>>X>>Y;
        g[X].push_back(Y);
        g[Y].push_back(X);
    }
    for(int i=1;i<=N;i++) parent[i]=-1;
    for(int i=1;i<=N;i++){
        if(!vis[i]) dfs(i);
    }

    for(int i=1;i<=N;i++) if(ap[i]) articulationCount++;
    cout<<articulationCount<<" "<<bridgeCount<<"\n";
}
