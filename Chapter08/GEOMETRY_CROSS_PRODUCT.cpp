#include <iostream>
using namespace std;

struct Point {
    int x, y;
};

int crossProduct(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int main() {
    Point o, a, b;
    cin >> o.x >> o.y >> a.x >> a.y >> b.x >> b.y;
    cout << crossProduct(o, a, b) << endl;
    return 0;
}
