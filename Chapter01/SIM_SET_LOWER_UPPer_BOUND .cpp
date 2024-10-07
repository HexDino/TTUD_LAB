#include <iostream>
#include <set>
#include <string>
#include <sstream>

int main() {
    int n;
    std::cin >> n;

    std::set<int> S;
    for (int i = 0; i < n; ++i) {
        int ai;
        std::cin >> ai;
        S.insert(ai);
    }

    std::string line;
    while (std::getline(std::cin, line) && line != "#") {
        std::istringstream iss(line);
        std::string operation;
        int v;
        iss >> operation >> v;

        if (operation == "min_greater_equal") {
            auto it = S.lower_bound(v);
            if (it != S.end()) {
                std::cout << *it << std::endl;
            } else {
                std::cout << "NULL" << std::endl;
            }
        } else if (operation == "min_greater") {
            auto it = S.upper_bound(v);
            if (it != S.end()) {
                std::cout << *it << std::endl;
            } else {
                std::cout << "NULL" << std::endl;
            }
        } else if (operation == "insert") {
            S.insert(v);
        } else if (operation == "remove") {
            S.erase(v);
        }
    }

    return 0;
}
