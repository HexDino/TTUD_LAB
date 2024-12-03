#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, T, D;
    cin >> N >> T >> D;
    vector<int> a(N), t(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> t[i];
    }
    vector<vector<int>> dp(N, vector<int>(T + 1, -1));
    for (int i = 0; i < N; ++i) {
        if (t[i] <= T) {
            dp[i][t[i]] = a[i];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int current_time = 0; current_time <= T; ++current_time) {
            if (dp[i][current_time] != -1) {
                for (int j = i + 1; j < N && j <= i + D; ++j) {
                    int new_time = current_time + t[j];
                    if (new_time <= T) {
                        dp[j][new_time] = max(dp[j][new_time], dp[i][current_time] + a[j]);
                    }
                }
            }
        }
    }
    int max_goods = 0;
    for (int i = 0; i < N; ++i) {
        for (int time = 0; time <= T; ++time) {
            max_goods = max(max_goods, dp[i][time]);
        }
    }

    cout << max_goods << endl;

    return 0;
}
