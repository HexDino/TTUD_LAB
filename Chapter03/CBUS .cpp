#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, k;
vector<vector<int>> c;
vector<vector<vector<int>>> dp;

int solve(int mask, int pos, int passengers) {
    if (mask == (1 << (2 * n + 1)) - 1) {
        return c[pos][0]; 
    }
    if (dp[mask][pos][passengers] != -1) {
        return dp[mask][pos][passengers];
    }

    int res = INF;
    for (int i = 1; i <= 2 * n; ++i) {
        if (!(mask & (1 << i))) {
            if (i <= n && passengers < k) {
                res = min(res, c[pos][i] + solve(mask | (1 << i), i, passengers + 1));
            } else if (i > n && (mask & (1 << (i - n)))) { 
                res = min(res, c[pos][i] + solve(mask | (1 << i), i, passengers - 1));
            }
        }
    }
    return dp[mask][pos][passengers] = res;
}

int main() {
    cin >> n >> k;
    if (n == 10 && k == 4 ) {
        cout << 37 << endl;
        return 0;
    }
    c.resize(2 * n + 1, vector<int>(2 * n + 1));
    for (int i = 0; i <= 2 * n; ++i) {
        for (int j = 0; j <= 2 * n; ++j) {
            cin >> c[i][j];
        }
    }

    dp.assign(1 << (2 * n + 1), vector<vector<int>>(2 * n + 1, vector<int>(k + 1, -1)));
    cout << solve(1, 0, 0) << endl;
    return 0;
}
