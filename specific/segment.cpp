
//do segments a and b intersect?
bool intersect(ppp a, ppp b)
{
    pll w = {a.fi.fi, a.fi.se}, y = {a.se.fi, a.se.se};
    pll x = {b.fi.fi, b.fi.se}, z = {b.se.fi, b.se.se};
    int p = ccw(w, x, y), q = ccw(w, z, y);
    int pp = ccw(x, w, z), qq = ccw(x, y, z);
    return (p != q && pp != qq);
}
//evaluate a segment p at x-coordinate X
ld eval(ppp p, int X)
{
    if (p.fi.fi == p.fi.se) return p.se.se;
    return ((ld) (p.se.se - p.se.fi) * (X - p.fi.fi) + (p.se.fi) * (p.fi.se - p.fi.fi)) / (p.fi.se - p.fi.fi);
}

struct cmp
{
    bool operator() (const int a, const int b) const
    {
        return eval(a) < eval(b);
    }
};

//among a list of segments inside the "coor" vector, finds one pair that intersects, if it exists. 
pii get(vi v)
{
    vpi events;
    for (int x : v)
    {
        events.PB({coor[x].fi.fi, -x - 1});
        events.PB({coor[x].se.fi, x});
    }
    sort(ALL(events));
    set<int, cmp> segs;
    for (pii e : events)
    {
        int idx = e.se; pii p;
        if (idx < 0)
        {
            idx = -idx; idx--;
            X = coor[idx].fi.fi;
            p = coor[idx].se;
            auto it = segs.LB(idx);
            if (it != segs.end() && intersect(coor[idx], coor[*it]))
            {
                return {*it, idx};
            }
            if (it != segs.begin() && intersect(coor[idx], coor[*prev(it)]))
            {
                return {*prev(it), idx};
            }
            segs.insert(idx);
        }
        else
        {
            X = coor[idx].se.fi;
            auto it = segs.erase(segs.find(idx));
            if (it != segs.end() && it != segs.begin() && intersect(coor[*it], coor[*prev(it)]))
            {
                return {*it, *prev(it)};
            }
        }
    }
    return {-1, -1};
}
