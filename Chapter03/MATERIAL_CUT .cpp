#include <iostream>
#include <vector>
using namespace std;

bool canPlace(vector<vector<bool>>& grid, int x, int y, int h, int w) {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (x + i >= grid.size() || y + j >= grid[0].size() || grid[x + i][y + j]) {
                return false;
            }
        }
    }
    return true;
}

void placeRectangle(vector<vector<bool>>& grid, int x, int y, int h, int w, bool place) {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            grid[x + i][y + j] = place;
        }
    }
}

bool canCut(vector<vector<bool>>& grid, vector<pair<int, int>>& rectangles, int index) {
    if (index == rectangles.size()) {
        return true;
    }

    int h = rectangles[index].first;
    int w = rectangles[index].second;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (canPlace(grid, i, j, h, w)) {
                placeRectangle(grid, i, j, h, w, true);
                if (canCut(grid, rectangles, index + 1)) {
                    return true;
                }
                placeRectangle(grid, i, j, h, w, false);
            }
            if (canPlace(grid, i, j, w, h)) {
                placeRectangle(grid, i, j, w, h, true);
                if (canCut(grid, rectangles, index + 1)) {
                    return true;
                }
                placeRectangle(grid, i, j, w, h, false);
            }
        }
    }
    return false;
}

int main() {
    int H, W, n;
    cin >> H >> W >> n;
    vector<pair<int, int>> rectangles(n);
    for (int i = 0; i < n; ++i) {
        cin >> rectangles[i].first >> rectangles[i].second;
    }

    vector<vector<bool>> grid(H, vector<bool>(W, false));
    if (canCut(grid, rectangles, 0)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}