#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double

int32_t main(){
    int n; cin >> n;
    vector <int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    int dp[n + 1][n + 1];
    for(int i = 0; i <= n; i++){
        dp[i][0] = 0;
    }
    for(int i = 0; i <= n; i++){
        dp[0][i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            
        }
    }
}