#include <bits/stdc++.h>
using namespace std;

int n,m;
int C[5001],D[5001];
vector<int> g[5001];
int dist[5001]; 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>C[i]>>D[i];
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> cost(n+1,1e9);
    vector<bool> done(n+1,false);
    cost[1]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    pq.push({0,1});

    while(!pq.empty()){
        auto [cd,u]=pq.top();pq.pop();
        if(cost[u]<cd) continue;
        if(u==n){
            cout<<cd<<"\n";
            return 0;
        }
        if(!done[u]){
            done[u]=true;
            int limit=D[u];
            vector<int> d2(n+1,-1);
            d2[u]=0;
            queue<int>q; q.push(u);
            while(!q.empty()){
                int cur=q.front();q.pop();
                if(d2[cur]==limit) continue;
                for(auto &nx: g[cur]){
                    if(d2[nx]==-1){
                        d2[nx]=d2[cur]+1;
                        if(d2[nx]<=limit) q.push(nx);
                    }
                }
            }
            for(int i=1;i<=n;i++){
                if(d2[i]!=-1 && i!=u){
                    int new_cost=cd+C[u];
                    if(new_cost<cost[i]){
                        cost[i]=new_cost;
                        pq.push({new_cost,i});
                    }
                }
            }
        }
    }

    cout<<-1<<"\n"; 
    return 0;
}
