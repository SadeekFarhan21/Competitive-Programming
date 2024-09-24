#include <bits/stdc++.h>
using namespace std;
#define int long long int

int sigma(int num)
{
    int total = 1;

    for (int i = 2; (int)i * i <= num; i++)
    {
        if (num % i == 0)
        {
            int e = 0;
            do
            {
                e++;
                num /= i;
            } while (num % i == 0);

            int sum = 0, pow = 1;
            do
            {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1)
    {
        total *= (1 + num);
    }
    return total;
}

int d(int num)
{
    int total = 1;
    for (int i = 2; (int)i * i <= num; i++)
    {
        if (num % i == 0)
        {
            int e = 0;
            do
            {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1)
    {
        total *= 2;
    }
    return total;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> answer;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            answer.push_back(i);
            if (n / i != i)
            {
                answer.push_back(n / i);
            }
        }
    }

    sort(answer.begin(), answer.end());
    cout << answer[0] << " " << answer[answer.size() - 1] << " " << answer.size() << " " << answer.size() << " ";
    int x = d(n);
    cout << x << " ";
    int y = sigma(n);
    cout << y << "\n";
}

int32_t main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}