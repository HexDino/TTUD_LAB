#include <bits/stdc++.h>
using namespace std;
struct P{long long x,y;};
long long crossp(const P&a,const P&b,const P&c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;vector<P>v(n),h;
    for(int i=0;i<n;i++)cin>>v[i].x>>v[i].y;
    sort(v.begin(),v.end(),[](auto &a,auto &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);});
    for(int i=0;i<n;i++){
        while(h.size()>=2&&crossp(h[h.size()-2],h[h.size()-1],v[i])<=0)h.pop_back();
        h.push_back(v[i]);
    }
    for(int i=n-2,t=h.size()+1;i>=0;i--){
        while(h.size()>=t&&crossp(h[h.size()-2],h[h.size()-1],v[i])<=0)h.pop_back();
        h.push_back(v[i]);
    }
    h.pop_back();
    cout<<h.size()<<"\n";
    for(auto &p:h)cout<<p.x<<" "<<p.y<<"\n";
}
