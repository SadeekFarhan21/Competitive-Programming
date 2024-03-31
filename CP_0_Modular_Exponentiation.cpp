#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main(){
    ll a, b, c; cin >> a >> b >> c;
    while(a != 0 && b != 0 && c != 0){
        cout << binpow(a, b, c) << "\n";
        cin >> a >> b >> c;
    }
    return 0;
}