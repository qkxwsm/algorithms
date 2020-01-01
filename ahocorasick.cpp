map<int, int> ch[MAXN];
int link[MAXN];

int ins(vi s)
{
	int node = 0;
	FOR(i, 0, SZ(s))
	{
		int c = s[i];
		if (ch[node].find(c) == ch[node].end())
		{
			ch[node][c] = T;
			T++;
		}
		node = ch[node][c];
	}
	return node;
}
void push_links()
{
	queue<int> q; q.push(0); link[0] = -1;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for (auto p : ch[u])
		{
			int c = p.fi, v = p.se, w = u;
			while(w != 0)
			{
				w = link[w];
				if (ch[w].find(c) != ch[w].end())
				{
					link[v] = w;
					break;
				}
			}
			q.push(v);
		}
	}
	return;
}
