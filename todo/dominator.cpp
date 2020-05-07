/* DOMINATOR TREE FOR UNDIRECTED GRAPHS */

#include <bits/stdc++.h>
 
using namespace std;
 
template<class T, class U>
void ckmin(T &a, U b)
{
    if (a > b) a = b;
}
 
template<class T, class U>
void ckmax(T &a, U b)
{
    if (a < b) a = b;
}
 
#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define SZ(x) ((int) (x).size())
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (auto i = (a); i < (b); i++)
#define FORD(i, a, b) for (auto i = (a) - 1; i >= (b); i--)
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
 
const int MAXN = 200013;
const ll LLINF = 2696969696969696969ll;
const int INF = 1000000007;
 
int N, M, S, T;
vpi edge[MAXN];
priority_queue<pll, vector<pll>, greater<pll> > pq;
ll dist[MAXN];
vi edge1[MAXN], rev[MAXN], edge2[MAXN];
int st[MAXN], dom[MAXN];
int parent[MAXN], ancestor[20][MAXN], depth[MAXN];
vi ord;
bitset<MAXN> seen;
int subtree[MAXN];
int ans;
 
void toposort(int u)
{
    seen[u] = true;
    for (int v : edge1[u])
    {
        if (!seen[v]) toposort(v);
    }
    ord.PB(u);
}
void dfs2(int u)
{
    subtree[u] = 1;
    for (int v : edge2[u])
    {
        dfs2(v);
        subtree[u] += subtree[v];
    }
    if (u != S)
    {
        ckmax(ans, subtree[u]);
    }
}
int lca(int u, int v)
{
    if (depth[u] >= depth[v]) swap(u, v);
    FORD(i, 20, 0)
    {
        if ((depth[v] - depth[u]) >= (1 << i)) v = ancestor[i][v];
    }
    if (u == v) return u;
    FORD(i, 20, 0)
    {
        if (ancestor[i][u] != ancestor[i][v])
        {
            u = ancestor[i][u];
            v = ancestor[i][v];
        }
    }
    return ancestor[0][u];
}
 
int32_t main()
{
    cout << fixed << setprecision(12);
    cerr << fixed << setprecision(4);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> S; S--;
    FOR(i, 0, M)
    {
        int u, v, d;
        cin >> u >> v >> d; u--; v--;
        edge[u].PB({d, v});
        edge[v].PB({d, u});
    }
    fill(dist, dist + N, LLINF);
    dist[S] = 0;
    fill(parent, parent + N + 1, N);
    pq.push({0, S});
    while(!pq.empty())
    {
        ll d = pq.top().fi; int u = pq.top().se;
        pq.pop();
        if (dist[u] != d) continue;
        for (auto e : edge[u])
        {
            int v = e.se;
            ll cand = d + e.fi;
            if (dist[v] > cand)
            {
                dist[v] = cand;
                pq.push({dist[v], v});
            }
        }
    }
    FOR(i, 0, N)
    {
        for (auto p : edge[i])
        {
            if (dist[p.se] == dist[i] + p.fi)
            {
                edge1[i].PB(p.se);
                rev[p.se].PB(i);
            }
        }
    }
    toposort(S);
    reverse(ALL(ord));
    FOR(i, 0, 20)
    {
        ancestor[i][N] = N;
    }
    for (int u : ord)
    {
        ancestor[0][u] = N;
        for (int v : rev[u])
        {
            int w = ancestor[0][u];
            ancestor[0][u] = (w == N ? v : lca(w, v));
        }
        FOR(i, 1, 20)
        {
            ancestor[i][u] = ancestor[i - 1][ancestor[i - 1][u]];
        }
        depth[u] = depth[ancestor[0][u]] + 1;
        if (u != S)
        {
            edge2[ancestor[0][u]].PB(u);
        }
    }
    dfs2(S);
    cout << ans << '\n';
}
