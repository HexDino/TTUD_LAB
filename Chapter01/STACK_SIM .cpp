#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

int main(){
    stack<int> s;
    string line;
    while (getline(cin, line) && line != "#"){
        istringstream iss(line);
        string operation;
        int v;
        iss >> operation >> v;
        if (operation == "PUSH"){
            s.push(v);
        }
        else {
            if (s.empty()){
                cout << "NULL\n";
                continue;
            }
            else {
                cout << s.top() << '\n';
                s.pop();
            }
        }
    }
}
