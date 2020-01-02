ll pr = 3;
vl roots;

ll expo(ll a, ll e)
{
	if (e == 0) return 1;
	if (e & 1)
	{
		return expo(a * a % INF, e >> 1) * a % INF;
	}
	return expo(a * a % INF, e >> 1);
}

void gen(int siz)
{
	if (SZ(roots) == siz) return;
	roots.resize(siz);
	roots[0] = 1;
	roots[1] = expo(pr, (INF - 1) / siz);
	FOR(i, 2, siz)
	{
		roots[i] = roots[i - 1] * roots[1] % INF;
	}
}
void ntt(vl &f)
{
	int siz = SZ(f);
	vl g(siz);
	for (int i = (siz >> 1); i; i >>= 1)
	{
		for (int j = 0; j < siz; j += i)
		{
			int t = (j << 1); if (t >= siz) t -= siz;
			FOR(k, 0, i)
			{
				g[j + k] = f[t + k] + roots[j] * f[i + t + k]; g[j + k] %= INF;
			}
		}
		swap(f, g);
	}
}

vl poly_mult(vl p, vl q)
{
	int deg = SZ(p) + SZ(q) - 1, siz = (1 << (32 - __builtin_clz(deg - 1)));
	vl res(deg);
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
