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
