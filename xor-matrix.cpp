#include <bits/stdc++.h>
#define MAXN 110005
using namespace std;
int N, flag;
int A[2][MAXN];
void calc(int p) {
    for (int i = 0; i < N; i++) {
        A[flag][i] = A[1 - flag][i] ^ A[1 - flag][(i + (1LL << p)) % N];
    }
    flag = 1 - flag;
}
int main() {
    cin >> N;
    long long Q; cin >> Q; Q--;
    for (int i = 0; i < N; i++)
        cin >> A[0][i];
    flag = 1;
    for (int k = 0; k < 60; k++) {
        if (Q & (1LL << k)) 
            calc(k);
    }
    for (int i = 0; i < N; i++)
        cout << A[1 - flag][i] << " ";
    return 0;
}
