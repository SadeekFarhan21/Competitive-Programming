#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
#define int long long
vector<vector<pair<int, int>>> adj(N);
vector<vector<pair<int, int>>> reversed(N);

int32_t main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b, wt = 1;
        cin >> a >> b;
        adj[a].push_back(b);
        reversed[b].push_back(a);
    }

    return 0;
}
