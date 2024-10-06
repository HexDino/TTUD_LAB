#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool isValidMove(int x, int y, int n, int m, const vector<vector<int>>& maze, vector<vector<bool>>& visited) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y];
}

int shortestPathToExit(int n, int m, int startX, int startY, const vector<vector<int>>& maze) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<tuple<int, int, int>> q;
    q.push({startX, startY, 0});
    visited[startX][startY] = true;

    while (!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();

        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            return steps;
        }

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            if (isValidMove(newX, newY, n, m, maze, visited)) {
                visited[newX][newY] = true;
                q.push({newX, newY, steps + 1});
            }
        }
    }

    return -1; 
}

int main() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;

    vector<vector<int>> maze(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maze[i][j];
        }
    }

    int result = shortestPathToExit(n, m, r - 1, c - 1, maze);
    if (result != -1 ) cout << result + 1 << endl;
    else cout << -1 << endl;

    return 0;
}