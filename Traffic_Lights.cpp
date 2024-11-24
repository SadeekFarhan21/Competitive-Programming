#include <bits/stdc++.h>
using namespace std;
#define int long long int
int32_t main()
{
    int l, n;
    cin >> l >> n;
    set<int> s;
    s.insert(0);
    s.insert(l);
    multiset<int> ms;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s.insert(a);
        auto lower = s.lower_bound(a);
        auto upper = s.upper_bound(a);
        int distance1 = *upper - *lower;
        // cout << *lower << " " << *upper << "\n";
        lower--;
        int distance2 = *upper - *lower;
        // cout << *lower << " " << "\n";
    }
    return 0;
}