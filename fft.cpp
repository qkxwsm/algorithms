typedef complex<ld> num;
typedef vector<num> poly;

const ld EPS = 1e-10;
const ld PI = 3.141592653589793;
poly roots;

void gen(int deg)
{
	roots.resize(deg);
	roots[0] = num(1, 0);
	roots[1] = num(cos(2.0 * PI / deg), sin(2.0 * PI / deg));
	FOR(i, 2, deg)
	{
		roots[i] = roots[i - 1] * roots[1];
	}
	return;
}
void fft(poly &f)
{
	int n = SZ(f);
	poly g(n);
	for (int i = n >> 1; i; i >>= 1)
	{
		for (int j = 0; j < n; j += i)
		{
			int t = (j << 1) - (((j << 1) >= n) ? n : 0);
			FOR(k, 0, i)
			{
				g[j + k] = f[t + k] + roots[j] * f[t + k + i];
			}
		}
		swap(f, g);
	}
}
vl poly_mult(vl p, vl q)
{
	int siz = SZ(p) + SZ(q) - 1, siz1 = (1 << (32 - __builtin_clz(siz)));
	vl res(siz);
	if (p <= 100 || q <= 100)
	{
 		FOR(i, 0, SZ(p))
		{
            		FOR(j, 0, SZ(q))
            		{
                		res[i + j] += p[i] * q[j];
            		}
        	}
        	return res;
    	}
	poly p1(SZ(p)), q1(SZ(q));
	FOR(i, 0, SZ(p)) p1[i] = num(p[i], 0);
	FOR(i, 0, SZ(q)) q1[i] = num(q[i], 0);
	gen(siz1);
	p1.resize(siz1); q1.resize(siz1);
	fft(p1);
	fft(q1);
	FOR(i, 0, siz1) p1[i] *= q1[i];
	fft(p1);
	FOR(i, 0, siz1) p1[i] /= siz1;
	reverse(p1.begin() + 1, p1.end());
	FOR(i, 0, siz)
	{
		res[i] = round(real(p1[i]));
	}
	return res;
}
