#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n; cin >> n;
    map <int, int> m;
    while(n % 2 == 0){
        m[2]++;
        n /= 2;
    }
    for(int i = 3; i * i <= n; i += 2){
        while(n % i == 0){
            m[i]++;
            n /= i;
        }
    }
    if(n > 2) {
        m[n]++;
    }
    int result = 1;
    for(auto x : m){
        result *= (x.second + 1);
    }
    cout << result << "\n";
}

int main(){
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
    return 0;
}