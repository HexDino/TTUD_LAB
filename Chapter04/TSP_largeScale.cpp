#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

int main() {
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));

    // Đọc ma trận khoảng cách
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
        }
    }

    // Bảng DP: dp[mask][i] -> chi phí tối thiểu để thăm tập hợp mask và kết thúc tại thành phố i
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1)); // Để theo dõi hành trình

    dp[1][0] = 0; // Bắt đầu từ thành phố 1 với chỉ thành phố 1 đã được thăm

    // Duyệt qua tất cả các trạng thái mask
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) continue; // Nếu thành phố i không nằm trong mask, bỏ qua

            // Duyệt qua các thành phố j để tìm đường đi tối thiểu đến i
            for (int j = 0; j < n; ++j) {
                if (j != i && (mask & (1 << j)) && dp[mask ^ (1 << i)][j] != INF) {
                    int newCost = dp[mask ^ (1 << i)][j] + dist[j][i];
                    if (newCost < dp[mask][i]) {
                        dp[mask][i] = newCost;
                        parent[mask][i] = j;
                    }
                }
            }
        }
    }

    // Tìm chi phí nhỏ nhất để quay lại thành phố 1 và kết thúc hành trình
    int result = INF;
    int lastCity = -1;
    for (int i = 1; i < n; ++i) {
        if (dp[(1 << n) - 1][i] + dist[i][0] < result) {
            result = dp[(1 << n) - 1][i] + dist[i][0];
            lastCity = i;
        }
    }

    // In kết quả chi phí
    cout << result << endl;

    // Tái tạo hành trình từ bảng parent
    vector<int> path;
    int mask = (1 << n) - 1;
    while (lastCity != -1) {
        path.push_back(lastCity + 1);
        int temp = lastCity;
        lastCity = parent[mask][lastCity];
        mask ^= (1 << temp);
    }
    path.push_back(1); // Thêm thành phố ban đầu (city 1)

    reverse(path.begin(), path.end());

    // In hành trình
    cout << n << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;

    return 0;
}
