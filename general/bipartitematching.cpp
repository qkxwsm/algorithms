vi edge[MAXN];
int match[MAXN];
bitset<MAXN> seen;

bool dfs(int u)
{
	if (seen[u]) return false;
	seen[u] = true;
	for (int v : edge[u])
	{
		if (match[v] == -1 || dfs(match[v]))
		{
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}
int matching()
{
	int res = 0;
	FOR(i, 0, N + M)
	{
		match[i] = -1;
	}
	FOR(i, 0, N)
	{
		seen.reset();
		if (dfs(i)) res++;
	}
	return res;
}
