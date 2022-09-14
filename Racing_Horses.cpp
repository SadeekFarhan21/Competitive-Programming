#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n; cin >> n;
    vector <int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector <int> s(n - 1);
    sort(v.begin(), v.end());
    for(int i = 0; i < n - 1; i++){
        s[i] = v[i + 1] - v[i];
    }
    sort(s.begin(), s.end());
    cout << s[0] << "\n";  
}

int main(){
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
    return 0;
}