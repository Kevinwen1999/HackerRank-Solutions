#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#define LOG_TWO_N 17	// 2^10 > 1000, adjust this value as needed
#define MAX_N 300030
#define MAXN 100010
#define INF 0x3f3f3f3f
#define ll unsigned long long
using namespace std;
int N, v1, v2, v3;
ll A, B, C;
ll ans;
vector <int> adj[MAXN];
ll idx = 0;
ll H[MAXN*3], E[MAXN*3], l[MAXN*3], node[1000500], depth[MAXN*3];
class RMQ {		// Range Minimum Query
private:
	ll _A[MAX_N], SpT[MAX_N][LOG_TWO_N];
public:
	void rmq(int n, ll A[])
	{
		// constructor as well as pre-processing routine
		for (int i = 0; i < n; i++)
		{
			_A[i] = A[i];
			SpT[i][0] = i; // RMQ of sub array starting at index i + length 2^0=1
		}

		// the two nested loops below have overall time complexity = O(n log n)
		for (int j = 1; (1<<j) <= n; j++)	// for each j s.t. 2^j <= n, O(log n)
			for (int i = 0; i + (1<<j) - 1 < n; i++)
			// for each valid i, O(n)
			if (_A[SpT[i][j-1]] < _A[SpT[i+(1<<(j-1))][j-1]])
			SpT[i][j] = SpT[i][j-1];	// start at index i of length 2^(j-1)
			else
			SpT[i][j] = SpT[i+(1<<(j-1))][j-1]; // start at index i+2^(j-1) of length 2^(j-1)
	}
	ll query(int i, int j) {
		// this query is O(1)
		int k = (int)floor(log((double)j-i+1) / log(2.0));	// 2^k <= (j-i+1)
		if (_A[SpT[i][k]] <= _A[SpT[j-(1<<k)+1][k]])
			return SpT[i][k];
		else
			return SpT[j-(1<<k)+1][k];
	}

};
//RMQ ST;
void buildtree(ll stidx, ll L, ll R)
{
    if (L > R) return;
    if (L==R)
    {
        node[stidx] = L;//assign value to node[stidx];
        return;
    }
    buildtree(2*stidx, L, (L+R)/2);
    buildtree(2*stidx + 1, (L+R)/2 + 1, R);
    node[stidx] = (l[node[2*stidx]] < l[node[2*stidx+1]])? node[2*stidx]: node[2*stidx+1];//assign value to node[stidx];
}
//call query(1,0,N-1,i,j);
ll query(int stidx, int L, int R, int &i, int &j) // i and j are the given range
{
    if (i > R || j < L) return -1; //out of range
    if (L >= i && R <= j) return node[stidx];
    ll p1 = query(2*stidx, L, (L+R)/2, i,j);
    ll p2 = query(2*stidx + 1, (L+R)/2 + 1, R, i,j);
    if (p1==-1) return p2;
    if (p2==-1) return p1;
    return (l[p1] < l[p2])? p1 : p2;//base on  the calculation, same as in buildtree;
}
void dfs(int cur, int dep, int pa)
{
    //occ[cur].insert(idx);
    depth[cur] = dep;
    H[cur] = idx;
    E[idx] = cur;
    l[idx++] = dep;
    for (auto v : adj[cur])
    {
        if (v==pa) continue;
        dfs(v, dep+1, cur);
        //occ[cur].insert(idx);
        E[idx] = cur;
        l[idx++] = dep;
    }
}
void init()
{
    B = min(2 * A, B);
    C = min(A + B, C);
    idx = 0;
    memset(&ans, 0x3f, sizeof ans);
    memset(E, 0, sizeof E);
    memset(depth, 0, sizeof depth);
    memset(H,0x3f,sizeof H);
    memset(l,0x3f,sizeof l);
    dfs(0,0,-1);
//    ST.rmq(idx, l);
    buildtree(1,0,idx - 1);
}
int lca(int a, int b) {
    int f1 = H[a], f2 = H[b];
    if (f1 > f2) swap(f1, f2);
    //return E[ST.query(f1, f2)];
    return E[query(1,0,idx - 1,f1,f2)];
}
int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}
// Always optimal to combine paths as fast as possible
ll calc1(int a, int b, int c) {
    int commonlca = lca(a, lca(b, c));
    if (lca(a, b) == commonlca) // lca(a, c) or lca(b, c) must be equal or lower than common lca, so combine at one of them first
        return min(A * dist(a, b) + B * dist(lca(a, c), c) + C * depth[c], A * dist(a, b) + B * dist(lca(b, c), c) + C * depth[c]);
    else
        return A * dist(a, b) + B * dist(lca(a, b), c) + C * depth[c];
}
ll calc2(int a, int b, int c) {
    int commonlca = lca(a, lca(b, c));
    if (lca(a, b) == commonlca)
        return min(A * (dist(a, b) + dist(c, lca(a, c))) + C * dist(lca(a, c), 0), A * (dist(a, b) + dist(c, lca(b, c))) + C * dist(lca(b, c), 0));
    else
        return A * (dist(a, b) + dist(c, commonlca)) + B * dist(lca(a, b), commonlca) + C * depth[commonlca];
}
ll calc(int a, int b, int c) {
    return min(calc1(a, b, c), calc2(a, b, c));
}
void exec() {
    cin>>N;
    cin>>A>>B>>C;
    cin>>v1>>v2>>v3;
    v1--; v2--; v3--;
    for (int i = 0; i < N; i++)
        adj[i].clear();
    for (int i = 0, a, b; i < N - 1; i++) {
        cin>>a>>b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    init();
    ans = min(ans, calc(v1, v2, v3));
    ans = min(ans, calc(v1, v3, v2));
    ans = min(ans, calc(v2, v3, v1));
    cout<<ans<<"\n";
}
int main() {
    int t; cin>>t;
    while(t--) {
        exec();
    }
    return 0;
}
