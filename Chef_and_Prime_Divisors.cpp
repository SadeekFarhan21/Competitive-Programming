#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<int, int>> primeFactorization(int n)
{
    vector<pair<int, int>> factors;

    int count = 0;
    while (n % 2 == 0)
    {
        count++;
        n /= 2;
    }
    if (count > 0)
        factors.push_back({2, count});

    for (int i = 3; i * i <= n; i += 2)
    {
        count = 0;
        while (n % i == 0)
        {
            count++;
            n /= i;
        }
        if (count > 0)
            factors.push_back({i, count});
    }

    if (n > 1)
    {
        factors.push_back({n, 1});
    }

    return factors;
}

void solve()
{
    int a, b;
    cin >> a >> b;
    vector<pair<int, int>> factors = primeFactorization(b);
    int count = 0;
    for (auto x : factors)
    {
        if (a % x.second == 0)
        {
            count++;
        }
    }
    if (factors.size() == count)
    {
        cout << "Yes" << "\n";
    }
    else
    {
        cout << "No" << "\n";
    }
    return;
}

int32_t main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
}