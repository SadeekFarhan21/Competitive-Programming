#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("output.txt", "w", stdout);
    int limit = 100000000;
    vector<int> answer;
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            answer.push_back(i);
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 0; i < answer.size(); i += 100) {
        cout << answer[i] << "\n";
    }

    return 0;
}
