#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    queue<int> a;
    int num = 1;
    for (int i = 0;i < n;i++) {
        a.push(i + 1);
    }
    while (a.empty() == false) {
        if (num == m) {
            cout << a.front() << " ";
            num = 1;
            a.pop();
        }
        else {
            num = num + 1;
            a.push(a.front());
            a.pop();
        }
    }
    return 0;
}