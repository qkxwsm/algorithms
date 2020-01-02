vi str;
int sval[MAXN], suf[MAXN], lcp[MAXN];
pair<pii, int> ord[MAXN];

void suffixarray()
{
	int n = SZ(str);
	FOR(i, 0, n)
	{
		sval[i] = str[i];
	}
	FOR(i, 0, 20)
	{
		FOR(j, 0, n)
		{
			ord[j] = {{sval[j], (j + (1 << i) < n ? sval[j + (1 << i)] : -1)}, j};
		}
		sort(ord, ord + n);
		sval[ord[0].se] = 0;
		FOR(j, 1, n)
		{
			sval[ord[j].se] = sval[ord[j - 1].se] + (ord[j].fi != ord[j - 1].fi);
		}
	}
	FOR(i, 0, n)
	{
		suf[sval[i]] = i;
	}
	int best = 0;
	FOR(i, 0, n)
	{
		if (sval[i] == n - 1)
		{
			lcp[i] = 0;
			continue;
		}
		int idx = suf[sval[i] + 1];
		while(i + best < n && idx + best < n && str[i + best] == str[idx + best]) best++;
		lcp[sval[i]] = best;
		if (best) best--;
	}
	return;
}
