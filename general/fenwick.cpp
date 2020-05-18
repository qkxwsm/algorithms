void update(int idx, ll v)
{
    for (int e = idx + 1; e < MAXN; e += e & (-e))
    {
        fen[e] += v;
    }
}
ll query(int idx)
{
    ll res = 0;
    for (int e = idx + 1; e; e -= e & (-e))
    {
        res += fen[e];
    }
    return res;
}
int kth(ll x) //acts like upper_bound
{
    //assert((res == 0 || query(res - 1) <= x) && query(res) > x);
    int res = 0;
    FORD(i, 20, 0)
    {
        if (res + (1 << i) < MAXN && fen[res + (1 << i)] <= x)
        {
            res += (1 << i);
            x -= fen[res];
        }
    }
    return res;
}
