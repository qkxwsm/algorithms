struct Line
{
    int a, b, c;
    //Line ax + by = c, with b >= 0.
};

int quadrant(int x, int y)
{
    if (x > 0 && y >= 0) return 1;
    if (x <= 0 && y > 0) return 2;
    if (x < 0 && y <= 0) return 3;
    if (x >= 0 && y < 0) return 4;
    return 0;
}
//sorts the lines by slope.
bool cmp(Line a, Line b)
{
    int qa = quadrant(a.a, a.b), qb = quadrant(b.a, b.b);
    if (qa != qb)
    {
        return qa < qb;
    }
    return (a.b * b.a < a.a * b.b);
}

//finds the intersection points of two lines
pdd intersect(Line p, Line q)
{
    ld a1 = p.a, b1 = p.b, c1 = p.c;
    ld a2 = q.a, b2 = q.b, c2 = q.c;
    pdd res;
    res.fi = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    res.se = (c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1);
    return res;
}
