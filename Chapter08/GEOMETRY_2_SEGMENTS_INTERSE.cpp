#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

int orientation(const Point &p, const Point &q, const Point &r) {
    long long val = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

bool onSegment(const Point &p, const Point &q, const Point &r) {
    if (min(p.x, q.x) <= r.x && r.x <= max(p.x, q.x) &&
        min(p.y, q.y) <= r.y && r.y <= max(p.y, q.y)) {
        return true;
    }
    return false;
}

bool intersect(const Point &p1, const Point &q1, const Point &p2, const Point &q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int n; 
    cin >> n;
    while (n--) {
        Point A, B, C, D;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
        cout << (intersect(A, B, C, D) ? 1 : 0) << "\n";
    }
    return 0;
}
