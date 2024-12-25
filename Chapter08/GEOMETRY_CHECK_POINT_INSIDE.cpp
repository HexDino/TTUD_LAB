#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

int crossProduct(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isConvexHull(const vector<Point>& points) {
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

bool isPointInside(Point p, const vector<Point>& hull) {
    int n = hull.size();
    for (int i = 0; i < n; ++i) {
        Point a = hull[i], b = hull[(i + 1) % n];
        if (crossProduct(a, b, p) < 0) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    if (!isConvexHull(points)) {
        for (int i = 0; i < n; ++i) cout << 0 << endl;
        return 0;
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        Point testPoint;
        cin >> testPoint.x >> testPoint.y;
        cout << (isPointInside(testPoint, points) ? 1 : 0) << endl;
    }

    return 0;
}
