#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 12;
const int MAXK = 5;
const int INF = INT_MAX / 2;

int n, K, Q;
int d[MAXN];
int c[MAXN + 1][MAXN + 1];
int D[1 << MAXN];
vector<int> feasible_subsets;

int dp[1 << MAXN][MAXK + 1];

int TSP_DP[1 << MAXN][MAXN];

int main() {
    cin >> n >> K >> Q;
    for (int i = 0; i < n; ++i)
        cin >> d[i];

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            cin >> c[i][j];

    int total_subsets = 1 << n;
    for (int mask = 1; mask < total_subsets; ++mask) {
        int total_demand = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                total_demand += d[i];
        if (total_demand <= Q) {
            feasible_subsets.push_back(mask);

            int subset_size = __builtin_popcount(mask);
            int subset_nodes[MAXN];
            int idx = 0;
            for (int i = 0; i < n; ++i)
                if (mask & (1 << i))
                    subset_nodes[idx++] = i + 1;

            int tsp_total_states = 1 << idx;
            for (int s = 0; s < tsp_total_states; ++s)
                for (int u = 0; u < idx; ++u)
                    TSP_DP[s][u] = INF;

            for (int u = 0; u < idx; ++u)
                TSP_DP[1 << u][u] = c[0][subset_nodes[u]];

            for (int s = 1; s < tsp_total_states; ++s) {
                for (int u = 0; u < idx; ++u) {
                    if (!(s & (1 << u))) continue;
                    for (int v = 0; v < idx; ++v) {
                        if (u == v || !(s & (1 << v))) continue;
                        int prev_s = s ^ (1 << u);
                        if (TSP_DP[prev_s][v] + c[subset_nodes[v]][subset_nodes[u]] < TSP_DP[s][u]) {
                            TSP_DP[s][u] = TSP_DP[prev_s][v] + c[subset_nodes[v]][subset_nodes[u]];
                        }
                    }
                }
            }
            int full_s = tsp_total_states - 1;
            int min_distance = INF;
            for (int u = 0; u < idx; ++u) {
                int distance = TSP_DP[full_s][u] + c[subset_nodes[u]][0];
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
            D[mask] = min_distance;
        }
    }

    for (int mask = 0; mask < total_subsets; ++mask)
        for (int k = 0; k <= K; ++k)
            dp[mask][k] = INF;
    dp[0][0] = 0;

    for (int k = 1; k <= K; ++k) {
        for (int mask = 0; mask < total_subsets; ++mask) {
            if (dp[mask][k - 1] == INF) continue;
            for (int s : feasible_subsets) {
                if ( (mask & s) == 0 ) {
                    int new_mask = mask | s;
                    if (dp[new_mask][k] > dp[mask][k - 1] + D[s]) {
                        dp[new_mask][k] = dp[mask][k - 1] + D[s];
                    }
                }
            }
        }
    }

    int full_mask = total_subsets - 1;
    int ans = INF;
    for (int k = 1; k <= K; ++k) {
        if (dp[full_mask][k] < ans) {
            ans = dp[full_mask][k];
        }
    }
    cout << ans << endl;
    return 0;
}
