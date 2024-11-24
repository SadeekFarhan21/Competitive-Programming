#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 9;
const int M = 2e5 + 9;
vector<int> components;
vector<bool> visited(N);
vector<int> adj[N];

void dfs(int node)
{
    visited[node] = true;
    for (auto neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            visited[neighbor] = true;
            dfs(neighbor);
        }
    }
}

int32_t main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            components.push_back(i);
            dfs(i);
        }
    }
    cout << components.size() - 1 << "\n";
    for (int i = 1; i < components.size(); i++)
    {
        cout << components[i - 1] << " " << components[i] << "\n";
    }
    return 0;
}