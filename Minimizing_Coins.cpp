#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n, x;
    cin >> n >> x;
    vector<long long> coins(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> coins[i];
    }
    vector<long long> dp(x + 1, INT_MAX);
    dp[0] = 0;
    for (long long i = 1; i <= n; i++)
    {
        for (long long weight = 0; weight <= x; weight++)
        {
            if (weight - coins[i - 1] >= 0)
            {
                dp[weight] = min(dp[weight], dp[weight - coins[i - 1]] + 1);
            }
        }
    }
    if (dp[x] == INT_MAX)
        cout << -1 << "\n";
    else
        cout << dp[x] << "\n";
    return 0;
}