vi pts[MAXN];
vi segpts[3 * MAXN], fen[3 * MAXN];

vi comb(vi l, vi r)
{
	vi res;
	int iter = 0;
	FOR(i, 0, SZ(l))
	{
		while(iter < SZ(r) && r[iter] <= l[i])
		{
			res.PB(r[iter]);
			iter++;
		}
		if (res.empty() || res.back() != l[i])
		{
			res.PB(l[i]);
		}
	}
	while(iter < SZ(r))
	{
		res.PB(r[iter]);
		iter++;
	}
	return res;
}
void build(int w, int L, int R)
{
	if (L == R)
	{
		segpts[w] = pts[L];
	}
	else
	{
		int mid = (L + R) >> 1;
		build(w << 1, L, mid);
		build(w << 1 | 1, mid + 1, R);
		segpts[w] = comb(segpts[w << 1], segpts[w << 1 | 1]);
	}
	fen[w].resize(SZ(segpts[w]) + 1);
	return;
}
void update(int w, int L, int R, int x, int y, int v)
{
	if (L != R)
	{
		int mid = (L + R) >> 1;
		if (x <= mid) update(w << 1, L, mid, x, y, v);
		else update(w << 1 | 1, mid + 1, R, x, y, v);
	}
	y = LB(ALL(segpts[w]), y) - segpts[w].begin();
	for (int e = y + 1; e < SZ(fen[w]); e += e & (-e))
	{
		fen[w][e] += v;
	}
	return;
}
ll query(int w, int L, int R, int x1, int x2, int y1, int y2)
{
	if (x1 <= L && R <= x2)
	{
		ll res = 0;
		y2 = UB(ALL(segpts[w]), y2) - segpts[w].begin() - 1;
		y1 = LB(ALL(segpts[w]), y1) - segpts[w].begin();
		for (int e = y2 + 1; e > 0; e -= e & (-e))
		{
			res += fen[w][e];
		}
		for (int e = y1; e > 0; e -= e & (-e))
		{
			res -= fen[w][e];
		}
		return res;
	}
	int mid = (L + R) >> 1;
	if (x2 <= mid) return query(w << 1, L, mid, x1, x2, y1, y2);
	if (mid < x1) return query(w << 1 | 1, mid + 1, R, x1, x2, y1, y2);
	return query(w << 1, L, mid, x1, x2, y1, y2) + query(w << 1 | 1, mid + 1, R, x1, x2, y1, y2);
}
