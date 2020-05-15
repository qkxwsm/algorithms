//See cf100570F

int parent[MAXN], depth[MAXN], weight[MAXN], subtree[MAXN];
bitset<MAXN> dead;
vi edge[MAXN];
vi ord;
ll ans;

void dfs(int u, int p)
{
	subtree[u] = 1;
	for (int v : edge[u])
	{
		if (dead[v] || v == p) continue;
		parent[v] = u;
		depth[v] = depth[u] + 1;
		weight[v] = weight[u] + cost[u][v];
		dfs(v, u);
		subtree[u] += subtree[v];
	}
	ord.PB(u);
}
void work(int u)
{
	for (int v : edge[u])
	{
		if (v == parent[u] || dead[v]) continue;
		work(v);
	}
	guys.PB({weight[u], depth[u]});
}
void proc(int u)
{
	dfs(u, N);
	int c = -1, sz = subtree[u];
	for (int v : ord)
	{
		int cur = sz - 1, mx = 0;
		for (int w : edge[v])
		{
			if (dead[w] || w == parent[v]) continue;
			cur -= subtree[w];
			ckmax(mx, subtree[w]);
		}
		ckmax(mx, cur);
		if (mx * 2 <= sz) c = v;
	}
	ord.clear();
	depth[c] = 0;
	weight[c] = 0;
	parent[c] = N;
	dfs(c, N);
	ord.clear();
	for (int v : edge[c])
	{
		if (dead[v]) continue;
		work(v);
		ans -= calc();
	}
	work(c);
	ans += calc();
	dead[c] = true;
	for (int v : edge[c])
	{
		if (dead[v]) continue;
		proc(v);
	}
}
