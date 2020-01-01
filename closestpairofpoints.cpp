int N;
pair<pll, int> arr[MAXN];
pii ans;
ll best = LLINF;

ll dist(pll a, pll b)
{
	return (a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se);
}

bool beats(pii a, pii b)
{
	return (MP(arr[a.fi].se, arr[a.se].se) > MP(arr[b.fi].se, arr[b.se].se));
}
void ckans(int a, int b)
{
	if (arr[a].se > arr[b].se) swap(a, b);
	ll d = dist(arr[a].fi, arr[b].fi);
	if (d < best || (d == best && beats(ans, MP(a, b))))
	{
		ans = MP(a, b);
		best = d;
	}
}

void solve(int L, int R)
{
	if (L == R)
	{
		return;
	}
	if (L + 1 == R)
	{
		ckans(L, R);
		return;
	}
	int mid = (L + R) >> 1;
	solve(L, mid);
	solve(mid + 1, R);
	ll x = arr[mid].fi.fi;
	vi pts;
	FOR(i, L, R + 1)
	{
		if ((arr[i].fi.fi - x) * (arr[i].fi.fi - x) <= best)
		{
			pts.PB(i);
		}
	}
	FOR(i, 0, SZ(pts))
	{
		FOR(j, i + 1, min(SZ(pts), i + 20))
		{
			ckans(pts[i], pts[j]);
		}
	}
}
