#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    int n, M;
    std::cin >> n >> M;

    std::vector<int> a(n);
    std::unordered_set<int> seen;
    long long Q = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        
        int complement = M - a[i];
        if (seen.find(complement) != seen.end()) {
            ++Q;
        }
        
        seen.insert(a[i]);
    }

    std::cout << Q << std::endl;

    return 0;
}
