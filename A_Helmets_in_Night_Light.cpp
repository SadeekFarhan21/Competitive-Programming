#include "bits/stdc++.h"
using namespace std;
#define int long long

void solve()
{
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    vector<int> b(n);
    map<int, int> m;
    int count = 0, total = 0;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++)
    {
        v[i] = {a[i], b[i]};
    }
    sort(v.begin(), v.end());
    

    // We would go till we have 
    for (int i = 0; i < n; i++)
    {
        v[i]
    }
}

int32_t main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}