#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> d(n);
    for(int &duration : d){
        cin >> duration;
        if(duration < 1){
            cerr << "Error: Job durations must be positive integers.\n";
            return 1;
        }
    }
    
    sort(d.begin(), d.end(), [&](const int &a, const int &b) -> bool {
        return a > b;
    });
    
    int T = 0;
    for(int i = 0; i < n; ++i){
        T = max(T, d[i] + i);
    }
    
    cout << T;
}
