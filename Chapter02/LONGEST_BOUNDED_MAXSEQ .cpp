#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    long long n, Q, a[1000005];
    cin >> n >> Q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    long long res = 0, S = 0, L = 1;
    for (int R = 1; R <= n; R++) {
        S += a[R];
        while (S > Q) {
            S -= a[L];
            L++;
        }
        res = max(res, R - L + 1);
    }
    if (res != 0) cout << res;
    else cout << -1;    
}
