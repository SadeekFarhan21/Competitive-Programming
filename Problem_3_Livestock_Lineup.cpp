#include <bits/stdc++.h>
using namespace std;

vector<int> adj[8];
vector<int> v(8);
ifstream input("lineup.in");
ofstream output("lineup.out");

map<string, int> m1 {
    {"Bessie", 0},
    {"Buttercup", 1},
    {"Belinda", 2},
    {"Beatrice", 3},
    {"Bella", 4},
    {"Blue", 5},
    {"Betsy", 6},
    {"Sue", 7}};

map<int, string> m2 {
    {0, "Bessie"},
    {1, "Buttercup"},
    {2, "Belinda"},
    {3, "Beatrice"},
    {4, "Bella"},
    {5, "Blue"},
    {6, "Betsy"},
    {7, "Sue"}};

void dfs(int node)
{
    v[node] = 1;
    output << m2[node] << "\n";
    for (auto u : adj[node]){
        if (!v[u]){
            dfs(u);
        }
    }
}

int main()
{
    
    
    int n; input >> n;
    for (int i = 0; i < n; i++){
        string w, x, y, z;
        string a, b;
        input >> a >> w >> x >> y >> z >> b;
        // cout << a << " " << b << "\n";
        adj[m1[a]].push_back(m1[b]);
        adj[m1[b]].push_back(m1[a]);
    }

    for (int i = 0; i < 8; i++){
        if (!v[i]){
            dfs(i, output);
        }
    }
    
    input.close();
    output.close();
    return 0;
}