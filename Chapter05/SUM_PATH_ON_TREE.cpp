#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long w;
};

int n;
vector<Edge> g[1000001];
int sz[1000001];
long long distSum[1000001];
long long ans = 0;
int N;

long long dfs1(int u,int p,long long depth){
    long long res=depth;
    sz[u]=1;
    for(auto &nx:g[u]){
        if(nx.to==p) continue;
        res+=dfs1(nx.to,u,depth+nx.w);
        sz[u]+=sz[nx.to];
    }
    return res;
}

void dfs2(int u,int p,long long curSum){
    ans = max(ans, curSum);
    for (auto &nx: g[u]){
        if(nx.to==p) continue;
        long long newSum = curSum + (N - 2LL*sz[nx.to])*nx.w;
        dfs2(nx.to,u,newSum);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1;i<=N-1;i++){
        int u,v; long long w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    long long initialSum = dfs1(1,-1,0);
    dfs2(1,-1,initialSum);
    cout<<ans<<"\n";
    return 0;
}
