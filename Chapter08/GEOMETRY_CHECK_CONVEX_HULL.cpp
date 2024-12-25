#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

int crossProduct(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool isConvexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return false;

    bool isCounterClockwise = false;
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        int nextNext = (i + 2) % n;
        int cross = crossProduct(points[i], points[next], points[nextNext]);

        if (i == 0) {
            isCounterClockwise = cross > 0;
        } else if ((cross > 0) != isCounterClockwise) {
            return false;
        }
    }

    return true;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        cout << (isConvexHull(points) ? 1 : 0) << endl;
    }

    return 0;
}
