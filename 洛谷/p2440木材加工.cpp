#include<bits/stdc++.h>
using namespace std;
long long n, m;
long long wood[100005]
bool check(int mid) {
    if mid == 0;return true;
    long long sum = 0
        for (int i = 0;i < n;i++) {
            sum += wood[i] / mid;
            if (sum >= m) return true;
        }
    return sum >= m;
}
int main() {
    long left = 0;
    long ans = 0;
    cin >> n >> m;
    long long  max_len = 0
        for (int i = 0;i < n;i++) {
            cin >> wood[i];
            max_len = max(max_len, wood[i]);
        }
    long long  right = max_len;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        }
        else {
            left = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}