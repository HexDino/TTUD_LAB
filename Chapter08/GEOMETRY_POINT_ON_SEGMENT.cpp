#include <iostream>
#include <vector>

using namespace std;

bool isPointOnSegment(int xA, int yA, int xB, int yB, int xC, int yC) {
    int crossProduct = (xA - xB) * (yC - yB) - (yA - yB) * (xC - xB);
    if (crossProduct != 0) return false;

    if (min(xB, xC) <= xA && xA <= max(xB, xC) && min(yB, yC) <= yA && yA <= max(yB, yC)) {
        return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int xA, yA, xB, yB, xC, yC;
        cin >> xA >> yA >> xB >> yB >> xC >> yC;
        cout << (isPointOnSegment(xA, yA, xB, yB, xC, yC) ? 1 : 0) << endl;
    }

    return 0;
}
