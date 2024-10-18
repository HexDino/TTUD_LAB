#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    ll a;
    ll max_even = LLONG_MIN;
    ll max_odd = LLONG_MIN;
    ll overall_max_even = LLONG_MIN;
    
    for(int i=0;i<n;i++){
        cin >> a;
        ll new_max_even = LLONG_MIN;
        ll new_max_odd = LLONG_MIN;
        
        if(a %2 ==0){
            new_max_even = max(a, (max_even != LLONG_MIN ? max_even + a : a));
            if(max_odd != LLONG_MIN){
                new_max_odd = max_odd + a;
            }
        }
        else{
            if(max_odd != LLONG_MIN){
                new_max_even = max_odd + a;
            }
            if(max_even != LLONG_MIN){
                new_max_odd = max(max_even + a, a);
            }
            else{
                new_max_odd = a;
            }
        }
        
        if(new_max_even != LLONG_MIN){
            overall_max_even = max(overall_max_even, new_max_even);
        }
        
        max_even = new_max_even;
        max_odd = new_max_odd;
    }
    
    if(overall_max_even == LLONG_MIN){
        cout << "NOT_FOUND";
    }
    else{
        cout << overall_max_even;
    }
}
