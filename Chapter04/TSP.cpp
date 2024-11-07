#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int main() {
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
        }
    }
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1][0] = 0; 

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) continue;

            for (int j = 0; j < n; ++j) {
                if (j != i && (mask & (1 << j)) && dp[mask ^ (1 << i)][j] != INF) {
                    dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + dist[j][i]);
                }
            }
        }
    }

    int result = INF;
    for (int i = 1; i < n; ++i) {
        if (dp[(1 << n) - 1][i] != INF) {
            result = min(result, dp[(1 << n) - 1][i] + dist[i][0]);
        }
    }

    cout << result << endl;

    return 0;
}
