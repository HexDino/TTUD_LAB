#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, L1, L2;
    cin >> n >> L1 >> L2;
    vector<ll> a(n+1, 0);
    for(int i=1;i<=n;i++) cin >> a[i];
    
    vector<ll> dp(n+1, 0);
    dp[0] = 0;
    
    vector<int> dq;
    dq.reserve(n+1);
    int head =0, tail=0;
    
    for(int i=1;i<=n;i++){
        if(i - L1 >=1){
            int j = i - L1;
            while(tail > head && dp[j] >= dp[dq[tail-1]]){
                tail--;
            }
            if(tail < dq.size()) {
                if(tail < dq.size()) dq[tail] = j;
            }
            else{
                dq.push_back(j);
            }
            tail++;
        }
        while(head < tail && dq[head] < i - L2){
            head++;
        }
        ll max_prev = 0;
        if(head < tail){
            max_prev = dp[dq[head]];
        }
        dp[i] = max(dp[i-1], a[i] + max_prev);
    }
    
    cout << dp[n];
}
