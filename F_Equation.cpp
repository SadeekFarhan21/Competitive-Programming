#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main()
{
    int r, n;
    cin >> r >> n;
    n += 1;
    n /= 2;
    int a = 1;
    int answer = a * (pow(r * r, n) - 1) / (pow(r, 2) - 1) - 1;
    cout << answer << "\n";
    return 0;
}