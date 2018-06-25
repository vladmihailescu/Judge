#include <bits/stdc++.h>

using namespace std;

int a[100005];

bool checker (int k, int g, int t) {
    for (int i = 1; i <= k; ++i) {
        if (a[i] >= g) {
            t -= (a[i] - g);
        }
    }
    return t >= 0;
}

int main()
{
    freopen ("ghiozdan.in", "r", stdin);
    freopen ("ghiozdan.out", "w", stdout);
    int d, k, t;
    cin >> d >> k >> t;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
    }
    a[k + 1] = d;
    k += 1;
    for (int i = k; i >= 1; --i) {
        a[i] -= a[i - 1];
    }
    int answer = -1;
    for (int power = 23; power >= 0; --power) {
        if (!checker(k, answer + (1 << power), t)) {
            answer += (1 << power);
        }
    }
    cout << answer + 1;
    return 0;
}