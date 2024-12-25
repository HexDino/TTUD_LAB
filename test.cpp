#include <bits/stdc++.h>
using namespace std;

static const long long INF = 1000000000000000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K, Q;
    cin >> n >> K >> Q;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    vector<vector<long long>> c(n+1, vector<long long>(n+1, INF));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> c[i][j];
        }
    }
    int M; cin >> M;
    vector<pair<int,int>> forbidden(M);
    for (int i = 0; i < M; i++) {
        cin >> forbidden[i].first >> forbidden[i].second;
        forbidden[i].first--;
        forbidden[i].second--;
    }

    int FULL = (1 << n);
    vector<int> demandSum(FULL, 0);
    for (int mask = 0; mask < FULL; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) sum += d[i];
        }
        demandSum[mask] = sum;
    }

    vector<bool> conflictCheck(FULL, true);
    for (int mask = 0; mask < FULL; mask++) {
        for (auto &pr : forbidden) {
            int i = pr.first, j = pr.second;
            if ((mask & (1 << i)) && (mask & (1 << j))) {
                conflictCheck[mask] = false;
                break;
            }
        }
    }

    vector<long long> costOneRoute(FULL, -1);
    for (int mask = 0; mask < FULL; mask++) {
        if (mask == 0) {
            costOneRoute[mask] = 0;
            continue;
        }
        if (!conflictCheck[mask]) continue;
        if (demandSum[mask] > Q) continue;
        vector<int> customers;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) customers.push_back(i+1);
        }
        int sz = (int)customers.size();
        int TSIZE = 1 << sz;
        vector<vector<long long>> dpTSP(TSIZE, vector<long long>(sz, INF));
        for (int k = 0; k < sz; k++) {
            dpTSP[1 << k][k] = c[0][customers[k]];
        }
        for (int s = 0; s < TSIZE; s++) {
            for (int last = 0; last < sz; last++) {
                if (dpTSP[s][last] == INF) continue;
                for (int nxt = 0; nxt < sz; nxt++) {
                    if (s & (1 << nxt)) continue;
                    long long nd = dpTSP[s][last] + c[customers[last]][customers[nxt]];
                    if (nd < dpTSP[s | (1 << nxt)][nxt]) {
                        dpTSP[s | (1 << nxt)][nxt] = nd;
                    }
                }
            }
        }
        long long best = INF;
        for (int last = 0; last < sz; last++) {
            long long val = dpTSP[TSIZE-1][last] + c[customers[last]][0];
            if (val < best) best = val;
        }
        if (best < INF) costOneRoute[mask] = best;
    }

    vector<vector<long long>> dp(FULL, vector<long long>(K+1, INF));
    dp[0][0] = 0;
    for (int mask = 0; mask < FULL; mask++) {
        for (int k = 0; k < K; k++) {
            if (dp[mask][k] == INF) continue;
            int remain = ((1 << n) - 1) ^ mask;
            for (int S = remain; S > 0; S = (S-1)&remain) {
                if (costOneRoute[S] < 0) continue;
                long long nd = dp[mask][k] + costOneRoute[S];
                if (nd < dp[mask | S][k+1]) dp[mask | S][k+1] = nd;
            }
            if (dp[mask][k] < dp[mask][k+1]) dp[mask][k+1] = dp[mask][k];
        }
    }

    long long ans = dp[FULL-1][K];
    if (ans == INF) ans = -1;
    cout << ans << "\n";

    return 0;
}



#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a(n+1, vector<long long>(m+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    const long long INF = 1000000000000000LL;
    vector<vector<long long>> dp(n+1, vector<long long>(m+1, INF));
    dp[1][1] = a[1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue;
            if (a[i][j] == 0) continue;
            long long val = INF;
            if (i > 1 && dp[i-1][j] != INF) val = min(val, dp[i-1][j] + a[i][j]);
            if (j > 1 && dp[i][j-1] != INF) val = min(val, dp[i][j-1] + a[i][j]);
            if (i > 1 && j > 1 && dp[i-1][j-1] != INF) val = min(val, dp[i-1][j-1] + a[i][j]);
            dp[i][j] = val;
        }
    }
    long long ans = dp[n][m];
    if (ans == INF) cout << -1 << "\n"; else cout << ans << "\n";
    return 0;
}
