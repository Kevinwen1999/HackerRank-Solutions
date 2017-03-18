#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
ull MOD;

void mulcomp (ull a, ull b, ull c, ull d, ull &e, ull &f){
    e = (((a%MOD)*(c%MOD))%MOD - ((b%MOD)*(d%MOD))%MOD + MOD)%MOD;
    f = (((a%MOD)*(d%MOD))%MOD + ((b%MOD)*(c%MOD))%MOD)%MOD;
}

pair <ull,ull> f(ull real, ull img, ull exp) {
    real%=MOD; img%=MOD;
    ull ar = 1, ai = 0;
    while (exp > 0){
        if (exp & 1){
            mulcomp(ar, ai, real, img, ar, ai);
        }
        mulcomp(real, img, real, img, real, img);
        exp>>=1;
    }
    return make_pair(ar, ai);
}

int main(){
    int T; cin>>T;
    ull a, b, c;
    while(T--){
        cin>>a>>b>>c>>MOD;
        pair<ull,ull> ans = f(a,b,c);
        cout<<ans.first<<" "<<ans.second<<"\n";
    }
}
