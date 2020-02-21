
//do segments a and b intersect?
bool intersect(ppp a, ppp b)
{
    pll w = {a.fi.fi, a.fi.se}, y = {a.se.fi, a.se.se};
    pll x = {b.fi.fi, b.fi.se}, z = {b.se.fi, b.se.se};
    int p = ccw(w, x, y), q = ccw(w, z, y);
    int pp = ccw(x, w, z), qq = ccw(x, y, z);
    return (p != q && pp != qq);
}
//evaluate a segment p at point a
ld eval(ppp p, int X)
{
    if (p.fi.fi == p.fi.se) return p.se.se;
    return ((ld) (p.se.se - p.se.fi) * (x - p.fi.fi) + (p.se.fi) * (p.fi.se - p.fi.fi)) / (p.fi.se - p.fi.fi);
}
