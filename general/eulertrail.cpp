//undirected graph
 
int N;
set<int> edge[MAXN];
vi ans;

void dfs(int u)
{
	while(!edge[u].empty())
	{
		int v = *edge[u].rbegin();
		edge[u].erase(prev(edge[u].end()));
		edge[v].erase(edge[v].find(u));
		dfs(v);
	}
	ans.PB(u);
}
 
int32_t main()
{
	int bad = 0, S = 0, T = 0;
	FOR(i, 0, SZ(compress))
	{
		if ((SZ(edge[i]) & 1))
		{
			bad++;
			if (bad == 1) S = i;
			if (bad == 2) T = i;
		}
	}
	if (bad != 0 && bad != 2)
	{
		cout << "-1\n";
		return 0;
	}
	if (bad == 2)
	{
		edge[S].insert(T);
		edge[T].insert(S);
	}
	dfs(S);
	if (bad == 2)
	{
		ans.pop_back();
		if (ans.back() != T)
		{
			for (int i = 0; ; i++)
			{
				if (ans[i] == S && ans[i + 1] == T || ans[i] == T && ans[i + 1] == S)
				{
					rotate(ans.begin(), ans.begin() + i, ans.end());
					ans.PB(ans[0]);
					ans.erase(ans.begin());
					break;
				}
			}
		}
	}
	return 0;
}

//directed graph

void dfs(int u)
{
    while(!edge[u].empty())
    {
        int v = edge[u].back();
        edge[u].pop_back();
        dfs(v);
    }
    tour.PB(u);
}
