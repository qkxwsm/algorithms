int N, M, T, C;
vi edge[MAXN], bcc[MAXN];
vpi edges;
int st[MAXN], ft[MAXN];
bitset<MAXN> seen;

void dfs(int u, int p)
{
	st[u] = T;
	ft[u] = T;
	T++;
	seen[u] = true;
	for (int v : edge[u])
	{
		if (v == p) continue;
		if (seen[v])
		{
			if (st[v] > st[u]) continue;
			edges.PB({u, v});
			ckmin(ft[u], st[v]);
			continue;
		}
		edges.PB({u, v});
		dfs(v, u);
		ckmin(ft[u], ft[v]);
		if (ft[v] >= st[u])
		{
			while(!edges.empty())
			{
				pii p = edges.back();
				edges.pop_back();
				bcc[p.fi].PB(C);
				bcc[p.se].PB(C);
				if (p == MP(u, v)) break;
			}
			C++;
		}
	}
}
