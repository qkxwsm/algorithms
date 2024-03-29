/* LCA Method 1: Sparse Table RMQ */

int N;
vi edge[MAXN];
vi ord;
int st[MAXN], depth[MAXN];
int table[20][2 * MAXN];

int comb(int u, int v)
{
    return (depth[u] > depth[v] ? v : u);
}
int query(int l, int r)
{
    int sz = 31 - __builtin_clz(r - l + 1);
    return comb(table[sz][l], table[sz][r - (1 << sz) + 1]);
}
void dfs(int u, int p)
{
    ord.PB(u);
    st[u] = SZ(ord) - 1;
    for (int v : edge[u])
    {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        ord.PB(u);
    }
}
int lca(int u, int v)
{
    u = st[u], v = st[v];
    if (u > v) swap(u, v);
    return query(u, v);
}

FOR(i, 0, SZ(ord))
{
	table[0][i] = ord[i];
}
FOR(i, 1, 20)
{
	FOR(j, 0, SZ(ord) - (1 << i) + 1)
	{
		table[i][j] = comb(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
	}
}

//answer for (u, v) is query(st[u], st[v])

/* LCA Method 2: Jump Pointers */

int lca(int u, int v)
{
    if (depth[u] > depth[v]) swap(u, v);
    FORD(i, 20, 0)
    {
        if ((depth[v] - depth[u]) >= (1 << i)) v = anc[i][v];
    }
    if (u == v) return u;
    FORD(i, 20, 0)
    {
        if (anc[i][u] != anc[i][v])
        {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return parent[u];
}


    FOR(i, 0, N + 1)
    {
        anc[0][i] = parent[i];
    }
    FOR(i, 1, 20)
    {
        FOR(j, 0, N + 1)
        {
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
        }
    }
