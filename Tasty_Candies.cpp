#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int total = 0;
    int answer = INT_MIN;
    for (int i = 0; i < n; i++) {
        total += v[i];
        if (total < 0) {
            total = 0;
        }
        answer = max(total, answer);
    }
    cout << answer << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}