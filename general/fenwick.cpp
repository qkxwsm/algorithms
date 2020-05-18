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
