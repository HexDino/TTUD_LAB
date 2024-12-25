#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll orientation(ll px, ll py, ll qx, ll qy, ll rx, ll ry) {
    return (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
}

bool onSegment(ll px, ll py, ll qx, ll qy, ll rx, ll ry) {
    return (min(px, rx) <= qx && qx <= max(px, rx) &&
            min(py, ry) <= qy && qy <= max(py, ry));
}

bool boundingBoxCheck(ll xA, ll yA, ll xB, ll yB, ll xC, ll yC, ll xD, ll yD) {
    if (max(xA, xB) < min(xC, xD)) return false;
    if (max(xC, xD) < min(xA, xB)) return false;
    if (max(yA, yB) < min(yC, yD)) return false;
    if (max(yC, yD) < min(yA, yB)) return false;
    return true;
}

bool doIntersect(ll xA, ll yA, ll xB, ll yB, ll xC, ll yC, ll xD, ll yD) {
    if (!boundingBoxCheck(xA, yA, xB, yB, xC, yC, xD, yD)) return false;
    ll o1 = orientation(xA, yA, xB, yB, xC, yC);
    ll o2 = orientation(xA, yA, xB, yB, xD, yD);
    ll o3 = orientation(xC, yC, xD, yD, xA, yA);
    ll o4 = orientation(xC, yC, xD, yD, xB, yB);
    if ((o1 > 0 && o2 < 0 || o1 < 0 && o2 > 0) &&
        (o3 > 0 && o4 < 0 || o3 < 0 && o4 > 0)) return true;
    if (o1 == 0 && onSegment(xA, yA, xC, yC, xB, yB)) return true;
    if (o2 == 0 && onSegment(xA, yA, xD, yD, xB, yB)) return true;
    if (o3 == 0 && onSegment(xC, yC, xA, yA, xD, yD)) return true;
    if (o4 == 0 && onSegment(xC, yC, xB, yB, xD, yD)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        ll xA, yA, xB, yB, xC, yC, xD, yD;
        cin >> xA >> yA >> xB >> yB >> xC >> yC >> xD >> yD;
        cout << (doIntersect(xA, yA, xB, yB, xC, yC, xD, yD) ? 1 : 0) << "\n";
    }
    return 0;
}
