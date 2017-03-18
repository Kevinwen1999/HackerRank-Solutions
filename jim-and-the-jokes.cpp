#include <bits/stdc++.h>
using namespace std;

int N;
unordered_map <int,int> ad;

void process (string ori, int base) {
    if (base == 1) return;
    reverse(ori.begin(), ori.end());
    int ans = 0;
    for (int i = 0; i < ori.size(); i++){
        int cur = ori[i] - '0';
        if (cur >=  base) return;
        ans += cur * pow(base, i);
    }
    ad[ans] ++;
}

int main() {
    cin>>N;
    for (int i = 0; i < N; i++) {
        string ori; int base;
        cin>>base>>ori;
        process(ori, base);
    }
    long long ans = 0;
    for (auto i : ad) {
        ans += 1LL*i.second*(i.second-1)/2;
    }
    cout<<ans<<"\n";
}
