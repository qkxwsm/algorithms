int N, Q, T;
vi edge[MAXN];
int subtree[MAXN], parent[MAXN], depth[MAXN], head[MAXN];
int st[MAXN], ft[MAXN];

void dfs(int u, int p)
{
    subtree[u] = 1;
    for (int v : edge[u])
    {
        if (v == p) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        subtree[u] += subtree[v];
    }
    if (u)
    {
        edge[u].erase(find(ALL(edge[u]), p));
    }
    FOR(i, 0, SZ(edge[u]))
    {
        if (subtree[edge[u][i]] > subtree[edge[u][0]])
        {
            swap(edge[u][0], edge[u][i]);
        }
    }
}
void dfs1(int u)
{
    st[u] = T;
    ft[u] = T;
    T++;
    FOR(i, 0, SZ(edge[u]))
    {
        int v = edge[u][i];
        head[v] = (i ? v : head[u]);
        dfs1(v);
        ft[u] = ft[v];
    }
}
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
int ask(int u, int v)
{
    int res = -INF;
    //u is ancestor of v.
    //what's the max on this path?
    while(true)
    {
        int w = head[v];
        if (depth[w] > depth[u])
        {
            ckmax(res, query(1, 0, N - 1, st[w], st[v]));
            v = parent[w];
        }
        else
        {
            ckmax(res, query(1, 0, N - 1, st[u], st[v]));
            break;
        }
    }
    return res;
}
