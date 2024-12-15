#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 509;
const int INF = 1e14 + 9;
int dist[N][N];

int32_t main()
{
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dist[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
    }

    for (int i = 1; i <= m; i++)
    {
        int a, b, wt;
        cin >> a >> b >> wt;
        dist[a][b] = min(dist[a][b], wt);
        dist[b][a] = min(dist[b][a], wt);
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF)
        {
            cout << -1 << "\n";
        }
        else
        {
            cout << dist[a][b] << "\n";
        }
    }
    return 0;
}