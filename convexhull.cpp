int sgn(ll x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}
int ccw(pll a, pll b, pll c)
{
	a.fi -= b.fi; a.se -= b.se;
	c.fi -= b.fi; c.se -= b.se;
	return sgn(a.fi * c.se - a.se * c.fi);
}

vi convexhull()
{
	vi upper, lower;
	upper.PB(0);
	FOR(i, 1, N)
	{
		while(SZ(upper) >= 2)
		{
			int x = upper[SZ(upper) - 2], y = upper[SZ(upper) - 1];
			if (ccw(coor[x], coor[y], coor[i]))
			{
				break;
			}
			upper.pop_back();
		}
		upper.PB(i);
	}
	upper.pop_back();
	lower.PB(N - 1);
	FORD(i, N - 1, 0)
	{
		while(SZ(lower) >= 2)
		{
			int x = lower[SZ(lower) - 2], y = lower[SZ(lower) - 1];
			if (ccw(coor[x], coor[y], coor[i]))
			{
				break;
			}
			lower.pop_back();
		}
		lower.PB(i);
	}
	lower.pop_back();
	vi res = upper;
	res.insert(res.end(), ALL(lower));
	return res;
}
