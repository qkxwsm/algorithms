int N, T, C;
vi nodes;
int st[MAXN], ft[MAXN];
bitset<MAXN> seen;

void dfs(int u)
{
	st[u] = T;
	ft[u] = T;
	nodes.PB(u);
	seen[u] = true;
	T++;
	for (int v : edge[u])
	{
		if (!seen[v]) dfs(v);
		ckmin(ft[u], ft[v]);
	}
	if (ft[u] == st[u])
	{
		while(true)
		{
			int v = nodes.back(); nodes.pop_back();
			scc[C].PB(v);
			st[v] = INF; ft[v] = INF;
			if (v == u) break;
		}
		C++;
	}
}
