#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//Extended Euclid
//if (d%c != 0) no solution
//x = x0 + (b/d)n, y = y0 - (a/d)n
ll x, y, d;
ll N, M, A, B, X;
unsigned long long pow_mod(unsigned long long a, unsigned long long b, unsigned long long n)
{
    if (b == 0) return 1;
    unsigned long long ans = pow_mod(a, b/2, n);
    ans = ans * ans % n;
    if (b%2 == 1) ans = ans * a % n;
    return ans;
}
void extendedeuclid(ll a, ll b, ll &x, ll &y, ll &d)
{
    if (b==0) {x = 1; y = 0; d = a; return;}
    extendedeuclid(b,a%b, x, y, d);
    ll x1 = y;
    ll y1 = x - (a/b)*y;
    x = x1;
    y = y1;
}
int main() {
    int T; cin>>T;
    while(T--) {
        cin>>A>>B>>X;
        if (B >= 0) {
            cout<<pow_mod(A, B, X)<<"\n";
        } else {
            extendedeuclid(X, A, x, y, d);
            cout<<pow_mod((y + X) % X, -B, X)<<"\n";
        }
    }
}
