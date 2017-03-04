#include <bits/stdc++.h>
using namespace std;

int N, a[100010], dp[100010][3];
string in = "0", temp;

int recur (int eid, int mod) // all substring starting at eid and starts with initial modulo sum mod
{
    if (eid > N) return 0;
    if (~dp[eid][mod]) return dp[eid][mod];
    return dp[eid][mod] =
        recur(eid+1, (mod + a[eid] % 3 ) % 3) + (a[eid] % 2 == 0 && (a[eid]%3 + mod)%3 == 0);
}

int main()
{
    memset(dp, -1, sizeof dp);
    cin >> temp;
    in += temp;
    N = in.size() - 1;
    for (int i = 1; i <= N; i++)
    {
        a[i] = in[i] - '0';
    }
    long long tot = 0;
    for (int i = 1; i <= N; i++)
    {
        if (a[i] == 0) tot++;
        else tot += recur(i, 0);
    }
    cout << tot << "\n";
}
