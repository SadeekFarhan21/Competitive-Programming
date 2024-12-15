#include <bits/stdc++.h>
using namespace std;
#define int long long

void dijkstra(int n, vector<vector<pair<int, int>>> &adj_list, int source)
{
    vector<int> dist(n + 1, LLONG_MAX);
    dist[source] = 0;
    set<pair<int, int>> s;
    s.insert({0, source});

    while (!s.empty())
    {
        int u = s.begin()->second;
        s.erase(s.begin());

        for (auto edge : adj_list[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v])
            {
                s.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                s.insert({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
}

int32_t main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<pair<int, int>>> adj_list(n + 1);

    for (int i = 0; i < e; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        adj_list[a].push_back({b, w});
    }

    dijkstra(n, adj_list, 1);

    return 0;
}
