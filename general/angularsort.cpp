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
