int head[MAXN], to[MAXN], link[MAXN], dist[MAXN], par[MAXN];
ll cap[MAXN];

void addedge(int u, int v, ll c, bool bi = false)
{
	link[E] = head[u];
	to[E] = v;
	cap[E] = c;
	head[u] = E;
	E++;
	link[E] = head[v];
	to[E] = u;
	cap[E] = (bi ? c : 0);
	head[v] = E;
	E++;
}
bool bfs()
{
	FOR(i, 0, T + 1)
	{
		dist[i] = INF;
		par[i] = -1;
	}
	dist[S] = 0;
	queue<int> q; q.push(S);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for (int e = head[u]; e; e = link[e])
		{
			if (cap[e] == 0) continue;
			int v = to[e];
			if (dist[v] <= dist[u] + 1) continue;
			dist[v] = dist[u] + 1;
			par[v] = e;
			q.push(v);
		}
	}
	return (dist[T] != INF);
}
ll aug(int u, ll f)
{
	if (u == T) return f;
	ll res = 0;
	for (int e = head[u]; e; e = link[e])
	{
		int v = to[e];
		if (dist[v] != dist[u] + 1 || cap[e] == 0) continue;
		int gain = aug(v, min(f, cap[e]));
		cap[e] -= gain;
		cap[e ^ 1] += gain;
		res += gain;
		f -= gain;
	}
	return res;
}
ll maxflow()
{
	ll res = 0;
	while(bfs())
	{
		res += aug(S, LLINF);
	}
	return res;
}
