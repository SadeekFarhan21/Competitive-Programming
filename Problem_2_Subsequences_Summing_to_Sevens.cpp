#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n; cin >> n;
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    vector <long long> v(n);
    vector <long long> sum(n);
    for(long long i = 0; i < n; i++){
        cin >> v[i];
    
    }
    sum[0] = v[0];
    for(long long i = 1; i < n; i++){
        sum[i] = sum[i - 1] + v[i];
    }
    long long count = 0;
    for(long long i = 0; i < n; i++){
        for(long long j = i + 1; j < n; j++){
            if((sum[j] - sum[i]) % 7 == 0){
                count = max(count, abs(j - i));
            }
        }
    }
    cout << count << "\n";
}