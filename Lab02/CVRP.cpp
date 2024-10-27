#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 12;
const int MAXK = 5;
const int INF = 1e9;

int n, K, Q;
int d[MAXN];
int c[MAXN + 1][MAXN + 1];

int total_demand[1 << MAXN];
int cost[1 << MAXN];
int dp[1 << MAXN][MAXK + 1];

int tsp_dp[1 << MAXN][MAXN];

int main() {
    cin >> n >> K >> Q;
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> c[i][j];
        }
    }

    for (int mask = 0; mask < (1 << n); ++mask) {
        total_demand[mask] = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                total_demand[mask] += d[i];
    }

    memset(cost, -1, sizeof(cost));
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (total_demand[mask] > Q) continue;

        int num_clients = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                num_clients++;

        int full = mask;
        for (int i = 0; i < (1 << n); ++i)
            for (int j = 0; j < n; ++j)
                tsp_dp[i][j] = INF;

        for (int u = 0; u < n; ++u) {
            if (mask & (1 << u)) {
                tsp_dp[1 << u][u] = c[0][u + 1];
            }
        }


        for (int m = 1; m < (1 << n); ++m) {
            if ((m & mask) != m) continue;
            for (int u = 0; u < n; ++u) {
                if (!(m & (1 << u))) continue;
                for (int v = 0; v < n; ++v) {
                    if (u == v) continue;
                    if (!(m & (1 << v))) continue;
                    if (tsp_dp[m ^ (1 << u)][v] + c[v + 1][u + 1] < tsp_dp[m][u]) {
                        tsp_dp[m][u] = tsp_dp[m ^ (1 << u)][v] + c[v + 1][u + 1];
                    }
                }
            }
        }

        int min_cost = INF;
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue;
            int route_cost = tsp_dp[mask][u] + c[u + 1][0];
            if (route_cost < min_cost) {
                min_cost = route_cost;
            }
        }
        cost[mask] = min_cost;
    }

    for (int i = 0; i < (1 << n); ++i)
        for (int k = 0; k <= K; ++k)
            dp[i][k] = INF;
    dp[0][0] = 0;

    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int k = 1; k <= K; ++k) {
            if (dp[mask][k - 1] == INF) continue;
            int remaining = ((1 << n) - 1) ^ mask;
            for (int sub = remaining; sub > 0; sub = (sub - 1) & remaining) {
                if (cost[sub] == -1) continue;
                if (dp[mask | sub][k] > dp[mask][k - 1] + cost[sub]) {
                    dp[mask | sub][k] = dp[mask][k - 1] + cost[sub];
                }
            }
        }
    }

    int result = INF;
    for (int k = 1; k <= K; ++k) {
        if (dp[(1 << n) - 1][k] < result) {
            result = dp[(1 << n) - 1][k];
        }
    }
    cout << result << endl;
    return 0;
}
