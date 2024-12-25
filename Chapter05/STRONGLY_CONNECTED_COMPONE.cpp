#include <bits/stdc++.h>
using namespace std;

vector<int> g[1000001], rg[1000001];
int N, M;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    for(int i=0; i<M; i++){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    vector<int> order, comp(N+1,-1), vis(N+1,0);
    function<void(int)> dfs1 = [&](int u){
        vis[u]=1;
        for(auto &nx: g[u]) if(!vis[nx]) dfs1(nx);
        order.push_back(u);
    };
    for(int i=1;i<=N;i++) if(!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());

    int idx=0;
    function<void(int,int)> dfs2 = [&](int u,int c){
        comp[u]=c;
        for(auto &nx: rg[u]) if(comp[nx]==-1) dfs2(nx,c);
    };

    for(auto &x:order) if(comp[x]==-1) dfs2(x,idx++);

    cout<<idx<<"\n";
}
