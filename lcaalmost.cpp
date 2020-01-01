int N, T;
vi edge[MAXN];
int parent[MAXN], st[MAXN], depth[MAXN];
int table[20][MAXN];

int comb(int u, int v)
{
	if (depth[u] != depth[v])
	{
		return (depth[u] > depth[v] ? v : u);
	}
	return (st[u] > st[v] ? u : v);
}
int query(int l, int r)
{
	int sz = 31 - __builtin_clz(r - l + 1);
	return comb(table[sz][l], table[sz][r - (1 << sz) + 1]);
}
void dfs(int u, int p)
{
	st[u] = T;
	T++;
	for (int v : edge[u])
	{
		if (v == p) continue;
		depth[v] = depth[u] + 1;
		parent[v] = u;
		dfs(v, u);
	}
}

FOR(i, 0, N)
{
	table[0][st[i]] = i;
}
FOR(i, 1, 20)
{
	FOR(j, 0, N - (1 << i) + 1)
	{
		table[i][j] = comb(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
	}
}

//ans for u, v is query(st[u] + 1, st[v])
