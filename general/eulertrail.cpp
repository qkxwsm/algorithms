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

//directed graph. note: you also need to check if the graph is connected! (not done here)

int32_t main()
{
    FOR(i, 0, N)
    {
        net[i] += SZ(edge[i]);
        for (int j : edge[i])
        {
            net[j]--;
        }
    }
    int neg = -1, pos = -1;
    FOR(i, 0, N)
    {
        if (net[i] < -1 || net[i] > 1)
        {
            cout << "NO\n";
            return 0;
        }
        if (net[i] == -1)
        {
            if (neg != -1)
            {
                cout << "NO\n";
                return 0;
            }
            neg = i;
        }
        if (net[i] == 1)
        {
            if (pos != -1)
            {
                cout << "NO\n";
                return 0;
            }
            pos = i;
        }
    }
    swap(pos, neg);
    if (neg != -1)
    {
        edge[pos].PB(neg);
        need = pos;
    }
    dfs(need);
    reverse(ALL(ord));
    if (neg != -1)
    {
        ord.pop_back();
        if (ord.back() == pos && ord.front() == neg)
        {
            //do nothing
        }
        else
        {
            FOR(i, 0, SZ(ord) - 1)
            {
                if (ord[i] == pos && ord[i + 1] == neg)
                {
                    rotate(ord.begin(), ord.begin() + i + 1, ord.end());
                    break;
                }
            }
        }
    }
}
