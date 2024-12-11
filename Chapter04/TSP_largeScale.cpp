#include <bits/stdc++.h>
using namespace std;

static int n;
static int c[1001][1001];
static const int INF = 1000000000;

inline int tourCost(const vector<int> &route) {
    int cost = 0;
    for (int i = 0; i < n; i++) {
        cost += c[route[i]-1][route[(i+1)%n]-1];
    }
    return cost;
}

static bool twoOptImprove(vector<int> &route) {
    bool improved = false;
    int bestDelta;
    do {
        bestDelta = 0;
        int bestI=-1,bestJ=-1;
        for(int i=0;i<n-1;i++){
            int A=route[i]-1, B=route[(i+1)%n]-1;
            for(int j=i+2;j<n;j++){
                if(j == i+1) continue;
                int C=route[j]-1, D=route[(j+1)%n]-1;
                int oldDist = c[A][B]+c[C][D];
                int newDist = c[A][C]+c[B][D];
                int delta = newDist - oldDist;
                if(delta<bestDelta){
                    bestDelta=delta;
                    bestI=i;bestJ=j;
                }
            }
        }
        if(bestDelta<0){
            reverse(route.begin()+bestI+1, route.begin()+bestJ+1);
            improved=true;
        }
    } while(bestDelta<0);
    return improved;
}

static bool threeOptImprove(vector<int> &route, int tries=1000) {
    bool improved = false;
    int currentCost = tourCost(route);
    mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    for (int attempt=0; attempt<tries; attempt++) {
        int a = (int)(rng()%n);
        int b = (int)(rng()%n);
        int c_ = (int)(rng()%n);

        vector<int> idx = {a,b,c_};
        sort(idx.begin(), idx.end());
        a=idx[0]; b=idx[1]; c_=idx[2];
        if(a==b || b==c_ || a==c_) continue;

        int A=route[a]-1;   int B=route[(a+1)%n]-1;
        int C=route[b]-1;   int D=route[(b+1)%n]-1;
        int E=route[c_]-1;  int F=route[(c_+1)%n]-1;

        int oldDist = c[A][B]+c[C][D]+c[E][F];

        auto try3opt = [&](bool rev1, bool rev2){
            vector<int> newRoute = route;
            if(rev1)
                reverse(newRoute.begin()+a+1, newRoute.begin()+b+1);
            if(rev2)
                reverse(newRoute.begin()+b+1, newRoute.begin()+c_+1);
            int newCost = tourCost(newRoute);
            if(newCost<currentCost){
                route=newRoute;
                currentCost=newCost;
                improved=true;
            }
        };

        try3opt(true,true);
        try3opt(true,false);
        try3opt(false,true);
        try3opt(false,false);
        if(improved) break;
    }
    return improved;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> c[i][j];
        }
    }

    if(n <= 20){
        int FULL = (1<<n);
        vector<vector<int>> dp(FULL, vector<int>(n, INF));
        vector<vector<int>> parent(FULL, vector<int>(n, -1));
        dp[1][0] = 0;

        for(int mask=1; mask<FULL; mask++){
            for(int i=0;i<n;i++){
                if(dp[mask][i] == INF) continue;
                for(int j=0;j<n;j++){
                    if(mask & (1<<j)) continue; 
                    int nextMask = mask | (1<<j);
                    int newCost = dp[mask][i] + c[i][j];
                    if(newCost < dp[nextMask][j]){
                        dp[nextMask][j] = newCost;
                        parent[nextMask][j] = i;
                    }
                }
            }
        }

        int bestCost = INF;
        int bestLast = -1;
        for(int i=1;i<n;i++){
            int costCycle = dp[FULL-1][i] + c[i][0];
            if(costCycle < bestCost){
                bestCost = costCycle;
                bestLast = i;
            }
        }

        vector<int> route;
        int curMask = FULL-1;
        int cur = bestLast;
        while(cur != -1){
            route.push_back(cur+1);
            int p = parent[curMask][cur];
            curMask ^= (1<<cur);
            cur = p;
        }
        reverse(route.begin(), route.end());
        cout << n << "\n";
        for (int i=0;i<n;i++){
            cout << route[i] << (i==n-1?'\n':' ');
        }

    } else {
        vector<int> bestRoute;
        int bestCost = INF;

        auto evaluate = [&](const vector<int> &rt){
            return tourCost(rt);
        };

        auto nearestNeighbor = [&](int start){
            vector<bool> visited(n,false);
            vector<int> route; 
            route.reserve(n);
            int current=start;
            visited[current]=true;
            route.push_back(current+1);
            for(int step=1;step<n;step++){
                int nextCity=-1; 
                int bestDist=INF;
                for(int j=0;j<n;j++){
                    if(!visited[j] && c[current][j]<bestDist){
                        bestDist=c[current][j];
                        nextCity=j;
                    }
                }
                visited[nextCity]=true;
                route.push_back(nextCity+1);
                current=nextCity;
            }
            return route;
        };

        vector<int> candidate = nearestNeighbor(0);
        {
            int val = evaluate(candidate);
            if(val<bestCost){
                bestCost=val;bestRoute=candidate;
            }
        }

        for(int s=1; s<min(n,5); s++){
            candidate = nearestNeighbor(s);
            int val = evaluate(candidate);
            if(val<bestCost){
                bestCost=val;bestRoute=candidate;
            }
        }

        {
            vector<int> rnd(n);
            iota(rnd.begin(), rnd.end(),1);
            for(int r=0;r<3;r++){
                shuffle(rnd.begin(), rnd.end(), mt19937_64(std::chrono::steady_clock::now().time_since_epoch().count()));
                int val = evaluate(rnd);
                if(val<bestCost){
                    bestCost=val;bestRoute=rnd;
                }
            }
        }

        twoOptImprove(bestRoute);
        threeOptImprove(bestRoute, 300); 

        cout << n << "\n";
        for (int i=0;i<n;i++){
            cout << bestRoute[i] << (i==n-1?'\n':' ');
        }
    }

    return 0;
}
