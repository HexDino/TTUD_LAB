#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string add_large_numbers(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string a, b;
    cin >> a >> b;

    string sum = add_large_numbers(a, b);

    cout << sum << endl;

    return 0;
}
