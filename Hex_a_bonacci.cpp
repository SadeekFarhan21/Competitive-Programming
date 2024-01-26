#include <iostream>
using namespace std;

const int MOD = 10000007;
const int MAXN = 10005; // Adjust this based on the problem constraints

int dp[MAXN];
int a, b, c, d, e, f, n;
int fn(int n) {
    dp[0] = a % MOD;
    dp[1] = b % MOD;
    dp[2] = c % MOD;
    dp[3] = d % MOD;
    dp[4] = e % MOD;
    dp[5] = f % MOD;

    for (int i = 6; i <= n; ++i) {
        dp[i] = (dp[i-1] % MOD + dp[i-2] % MOD + dp[i-3] % MOD + dp[i-4] % MOD + dp[i-5] % MOD) % MOD;
    }

    return dp[n];
}

int main() {
    int cases;
    scanf("%d", &cases);

    for (int caseno = 1; caseno <= cases; ++caseno) {
        scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &n);
        printf("Case %d: %d\n", caseno, fn(n));
    }

    return 0;
}
