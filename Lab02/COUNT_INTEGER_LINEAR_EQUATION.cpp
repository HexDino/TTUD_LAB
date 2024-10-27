#include <iostream>
#include <vector>

using namespace std;

int count_solutions(int n, int M, vector<int>& a) {

    int S = 0;
    for (int i = 0; i < n; ++i) {
        S += a[i];
    }

    int target = M - S;

    if (target < 0) {
        return 0;
    }

    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = a[i]; j <= target; ++j) {
            dp[j] += dp[j - a[i]];
        }
    }
    return dp[target];
}

int main() {
    int n, M;
    cin >> n >> M;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = count_solutions(n, M, a);
    cout << ans << endl;

    return 0;
}
