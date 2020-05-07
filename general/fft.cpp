//sum convolution

typedef complex<ld> num;
typedef vector<num> poly;

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
vl conv(vl p, vl q)
{
    int siz = SZ(p) + SZ(q) - 1, siz1 = (1 << (32 - __builtin_clz(siz)));
    vl res(siz);
    if (SZ(p) <= 100 || SZ(q) <= 100)
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

//sum convolution modulo p

const int INF = 998244353; //or (5 << 25), (7 << 26)
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
vi conv(vi p, vi q)
{
    int deg = SZ(p) + SZ(q) - 1, siz = (1 << (32 - __builtin_clz(deg - 1)));
    if (min(SZ(p), SZ(q)) <= 100)
    {
        vi res(deg);
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

//xor convolution

void xorfft(vl &f)
{
    int n = 31 - __builtin_clz(SZ(f));
    FOR(i, 0, n)
    {
        FOR(j, 0, SZ(f))
        {
            if (j & (1 << i)) continue;
            ll a = f[j], b = f[j + (1 << i)];
            f[j] = a + b;
            f[j + (1 << i)] = a - b;
        }
    }
}
vl conv(vl p, vl q)
{
    int siz = (1 << (32 - __builtin_clz(max(SZ(p), SZ(q)) - 1)));
    p.resize(siz);
    q.resize(siz);
    fwht(p);
    fwht(q);
    FOR(i, 0, siz)
    {
        p[i] *= q[i];
    }
    fwht(p);
    FOR(i, 0, siz)
    {
        p[i] /= siz;
    }
    return p;
}

//or convolution. 

//note: when rev is false, this is essentially sum over subsets!
void fwht(vl &f, bool rev)
{
    int n = 31 - __builtin_clz(SZ(f));
    FOR(i, 0, n)
    {
        FOR(j, 0, SZ(f))
        {
            if (j & (1 << i)) continue;
            //for and convolution, swap the indices below
            if (rev) f[j + (1 << i)] -= f[j];
            else f[j + (1 << i)] += f[j];
        }
    }
}
vl poly_mult(vl p, vl q)
{
    int siz = (1 << (32 - __builtin_clz(max(SZ(p), SZ(q)) - 1)));
    if (min(SZ(p), SZ(q)) <= 100)
    {
        vl res(siz);
        FOR(i, 0, SZ(p))
        {
            FOR(j, 0, SZ(q))
            {
                res[i | j] += p[i] * q[j];
            }
        }
        return res;
    }
    p.resize(siz);
    q.resize(siz);
    fwht(p, false);
    fwht(q, false);
    FOR(i, 0, siz)
    {
        p[i] *= q[i];
    }
    fwht(p, true);
    return p;
}
