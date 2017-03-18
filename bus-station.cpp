#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;

int N;
int pre[MAXN];
unordered_set <int> M;
set<int> ans;
int main() {
    cin>>N;
    for (int i = 1; i <= N; i++){
        cin>>pre[i];
        pre[i] += pre[i-1];
        M.insert(pre[i]);     
    }
    for (int i = 1; i <= N; i++){
        if (pre[N]%pre[i]!=0) continue;
        bool valid = true;
        for (int j = 2; j <= pre[N]/pre[i] && valid; j++){
            if (!M.count(pre[i]*j))
                valid = false;
        }
        if (valid)
            ans.insert(pre[i]);
    }
    for (int i : ans)
        cout<<i<<" ";
    return 0;
}
