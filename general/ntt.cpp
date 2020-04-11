const int INF = 998244353;
int pr = 3;
vi roots;

void gen(int siz)
{
    if (SZ(roots) == siz) return;
    roots.resize(siz);
    roots[0] = 1;
    roots[1] = pwr(pr, (INF - 1) / siz);
    FOR(i, 2, siz)
    {
        roots[i] = mul(roots[i - 1], roots[1]);
    }
}
void ntt(vi &f)
{
    int siz = SZ(f);
    vi g(siz);
    for (int i = (siz >> 1); i; i >>= 1)
    {
        for (int j = 0; j < siz; j += i)
        {
            int t = (j << 1); if (t >= siz) t -= siz;
            FOR(k, 0, i)
            {
                g[j + k] = add(f[t + k], mul(roots[j], f[i + t + k]));
            }
        }
        swap(f, g);
    }
}
vi poly_mult(vi p, vi q)
{
    int deg = SZ(p) + SZ(q) - 1, siz = (1 << (32 - __builtin_clz(deg - 1)));
    vi res(deg);
    if (min(SZ(p), SZ(q)) <= 100)
    {
        FOR(i, 0, SZ(p))
        {
            FOR(j, 0, SZ(q))
            {
                res[i + j] = add(res[i + j], mul(p[i], q[j]));
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
        p[i] = mul(p[i], q[i]);
    }
    ntt(p);
    int dd = pwr(siz, INF - 2);
    FOR(i, 0, siz)
    {
        p[i] = mul(p[i], dd);
    }
    reverse(p.begin() + 1, p.end());
    p.resize(deg);
    return p;
}
