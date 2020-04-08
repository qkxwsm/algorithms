int quadrant(pll a)
{
    if (a.se >= 0 && a.fi > 0) return 1;
    if (a.se > 0 && a.fi <= 0) return 2;
    if (a.se <= 0 && a.fi < 0) return 3;
    if (a.se < 0 && a.fi >= 0) return 4;
    return 0;
}

bool cmp(pll a, pll b)
{
    if (quadrant(a) != quadrant(b))
    {
        return quadrant(a) < quadrant(b);
    }
    return a.se * b.fi < a.fi * b.se;
}

bool between(pll a, pll b, pll c)
{
    if (cmp(a, c))
    {
        return cmp(a, b) && cmp(b, c);
    }
    else
    {
        return !(cmp(c, b) && cmp(b, a));
    }
}
ll tris(vpl v) //how many triangles contain the origin?
{
    int n = SZ(pts);
    ll res = 0;
    sort(ALL(pts), cmp);
    int iter = 0;
    FOR(i, 0, n)
    {
        pll opp = {-pts[i].fi, -pts[i].se};
        while(iter + 1 < i + n && between(pts[i], pts[(iter + 1) % n], opp)) iter++;
        ll num = iter - i;
        res += c2(num);
        res += c2(n - 1 - num);
    }
    res /= 2;
    res = c3(n) - res;
    return res;
}
