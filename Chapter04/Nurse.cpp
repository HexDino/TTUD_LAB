#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 +7;

int main(){
    int N, K1, K2;
    cin >> N >> K1 >> K2;
    vector<vector<int>> dp(N+1, vector<int>(2, 0));
    dp[0][0] =1;
    dp[0][1] =0;
    for(int i=1;i<=N;i++){
        ll w =0;
        for(int l=K1;l<=K2;l++){
            if(i >=l){
                if(i ==l){
                    w = (w +1) % MOD;
                }
                else{
                    w = (w + dp[i -l][1]) % MOD;
                }
            }
        }
        dp[i][0] = w;
        if(i >=1){
            dp[i][1] = dp[i-1][0];
        }
        else{
            dp[i][1] =0;
        }
    }
    ll M = ((ll)dp[N][0] + dp[N][1]) % MOD;
    if(K1 <=N && N <=K2){
        M = (M -1 + MOD) % MOD;
    }
    cout << M;
}
