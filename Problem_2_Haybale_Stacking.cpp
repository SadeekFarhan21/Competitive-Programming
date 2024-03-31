#include <bits/stdc++.h>
using namespace std;
#define ll long long

double findMedian(std::vector<ll>& nums) {
    std::sort(nums.begin(), nums.end());
    ll n = nums.size();
    if (n % 2 == 0) {
        // If the number of elements is even, average the middle two elements
        return (nums[n/2 - 1] + nums[n/2]) / 2.0;
    } else {
        // If the number of elements is odd, return the middle element
        return nums[n/2];
    }
}

int main(){
    // freopen("stacking.in", "r", stdin);
    // freopen("stacking.out", "w", stdin);
    
    ll n; cin >> n;
    vector <ll> v(n);
    ll k; cin >> k;
    for(ll i = 0; i < n; i++){
        ll a, b; cin >> a >> b;
        for(ll i = a; i <= b; i++){
            v[i - 1]++; 
        }
    }
    sort(v.begin(), v.end());
    double answer = findMedian(v);
    cout << answer << "\n";
}