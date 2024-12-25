#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> computeLPSArray(const string &P) {
    int m = P.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (P[i] == P[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

int countOccurrences(const string &P, const string &T) {
    int m = P.length();
    int n = T.length();
    vector<int> lps = computeLPSArray(P);
    int i = 0;
    int j = 0;
    int count = 0;

    while (i < n) {
        if (P[j] == T[i]) {
            i++;
            j++;
        }

        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && P[j] != T[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return count;
}

int main() {
    string P, T;
    getline(cin, P);
    getline(cin, T);

    cout << countOccurrences(P, T) << endl;

    return 0;
}
