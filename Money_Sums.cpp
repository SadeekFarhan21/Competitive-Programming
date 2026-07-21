#include "bits/stdc++.h"
using namespace std;

int32_t main() {
    int n;
    cin >> n;
    vector<int> v(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
    }

    vector<vector<bool>> dp(n, vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    // each individual item to be true
    for (int i = 0; i < n; i++) {
        dp[i][v[i]] = true;
    }
    for (int i = 1; i <= sum; i++) {
        for (int j = 0; j < n; j++) {
            if (i - v[j] >= 0) {
                dp[j][i] = dp[j - 1][i] + dp[j][v[i]];
            }
        }
    }
    return 0;
}