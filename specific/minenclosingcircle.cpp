typedef pair<ld, ld> pdd;

ld dist(pdd &a, pdd &b)
{
	return (a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se);
}
pdd circumcenter(pdd a, pdd b, pdd c)
{
	a.fi -= b.fi; a.se -= b.se;
	c.fi -= b.fi; c.se -= b.se;
	complex<ld> x = complex<ld>(a.fi, a.se);
	complex<ld> y = complex<ld>(c.fi, c.se);
	complex<ld> res = x * y * (conj(x - y)) / (conj(x) * y - x * conj(y));
	return {real(res) + b.fi, imag(res) + b.se};
}
pair<pdd, ld> get(vector<pdd> vec)
{
	pdd cen = {LLINF, LLINF}; ld rad = 0.0;
	if (SZ(vec) == 1)
	{
		cen = vec[0];
		rad = 0.0;
	}
	if (SZ(vec) == 2)
	{
		cen = {0.5 * (vec[0].fi + vec[1].fi), 0.5 * (vec[0].se + vec[1].se)};
		rad = 0.25 * dist(vec[0], vec[1]);
	}
	if (SZ(vec) == 3)
	{
		pdd c = circumcenter(vec[0], vec[1], vec[2]);
		ld d = dist(vec[0], c);
		cen = c;
		rad = d;
	}
	return {cen, rad};
}
pair<pdd, ld> solve()
{
	if (sz == 0 || SZ(know) >= 3)
	{
		return get(know);
	}
	pdd p = vec[sz - 1];
	sz--;
	pair<pdd, ld> res;
	res = solve();
	if (dist(res.fi, p) > res.se + EPS)
	{
		know.PB(p);
		res = solve();
		know.pop_back();
	}
	sz++;
	return res;
}
ld calc(vector<pdd> v)
{
	random_shuffle(ALL(v));
	if (SZ(v) <= 1) return 0.0;
	vec = v;
	sz = SZ(vec);
	know.clear();
	auto res = solve();
	return sqrt(res.se);
}
