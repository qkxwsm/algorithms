//just the functions

const int INF = 1000000007;

int add(int a, int b)
{
    a += b; if (a >= INF) a -= INF; return a;
}
int mul(int a, int b)
{
    return (ll) a * b % INF;
}
int sub(int a, int b)
{
    a -= b; if (a < 0) a += INF; return a;
}
int pwr(int a, int b)
{
    int res = 1;
    while(b > 0)
    {
        if (b & 1) res = mul(res, a);
        b >>= 1;
        a = mul(a, a);
    }
    return res;
}
int inv(int a)
{
    return pwr(a, INF - 2);
}
int dvd(int a, int b)
{
    return mul(a, inv(b));
}

//the class

struct modint
{
    int val;
    modint(ll v)
    {
        v %= INF;
        if (v < 0) v += INF;
        val = v;
    }
    modint()
    {
        modint(0);
    }
    void operator += (const modint m)
    {
        val += m.val;
        if (val >= INF) val -= INF;
    }
    void operator -= (const modint m)
    {
        val -= m.val;
        if (val < 0) val += INF;
    }
    void operator *= (const modint m)
    {
        val = ((ll) val * m.val % INF);
    }
};

modint operator +(modint a, modint b)
{
    return modint(a.val + b.val);
}
modint operator -(modint a, modint b)
{
    return modint(a.val + b.val);
}
modint operator *(modint a, modint b)
{
    return modint((ll)a.val * b.val);
}
modint pow(modint a, ll e)
{
    modint res = 1;
    for (; e; e >>= 1)
    {
        if (e & 1) res = res * a;
        a = a * a;
    }
    return res;
}
modint operator / (modint a, modint b)
{
    return a * pow(b, INF - 2);
}
