vl poly_mult(vl p, vl q)
{
	int deg = SZ(p) + SZ(q) - 1, siz = (1 << (32 - __builtin_clz(deg - 1)));
	vl res(deg);
	if (min(SZ(p), SZ(q)) <= 100)
	{
		FOR(i, 0, SZ(p))
		{
			FOR(j, 0, SZ(q))
			{
				res[i + j] += p[i] * q[j];
				res[i + j] %= INF;
			}
		}
		return res;
	}
	p.resize(siz);
	q.resize(siz);
	gen(siz);
	ntt(p); ntt(q);
	FOR(i, 0, siz)
	{
		p[i] *= q[i];
		p[i] %= INF;
	}
	ntt(p);
	ll inv = expo(siz, INF - 2);
	FOR(i, 0, siz)
	{
		p[i] *= inv; p[i] %= INF;
	}
	reverse(p.begin() + 1, p.end());
	p.resize(deg);
	return p;
}
