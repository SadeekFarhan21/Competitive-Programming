#include <bits/stdc++.h>
using namespace std;
#define int long long int

int32_t main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            pre[i + 1] = pre[i] + a[i];
        }

        int total_sum = pre[n];
        int k = n / 2 - 1;

        int bessie_final = LLONG_MAX;
        for (int x = 0; x <= k; x++)
        {
            int left = x;
            int right = n - (k - x);
            int segment_sum = pre[right] - pre[left];
            if (segment_sum < bessie_final)
            {
                bessie_final = segment_sum;
            }
        }

        int bessie = bessie_final;
        int elsie = total_sum - bessie;
        cout << bessie << " " << elsie << "\n";
    }
    return 0;
}
