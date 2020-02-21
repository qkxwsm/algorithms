pdd operator +(const pdd &a, const pdd &b)
{
        return {a.fi + b.fi, a.se + b.se};
}
pdd operator -(const pdd &a, const pdd &b)
{
        return {a.fi - b.fi, a.se - b.se};
}
 
template<class T> int sgn(T x)
{
        if (x < 0)
        {
                return -1;
        }
        if (x > 0)
        {
                return 1;
        }
        return 0;
}
struct circle
{
        pdd center;
        ld radius;
};
 
 
ld dist(pdd a, pdd b)
{
        return sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}
ld arcdist(circle c, pdd a, pdd b)
{
        //distance from a to b along c
        ld r = c.radius;
        ld d = dist(a, b);
        ld angle = 2.0 * asin(d / (2.0 * r));
        if (std::isnan(angle))
        {
                return PI * r;
        }
        return r * angle;
}
pdd rotate(pdd trans, ld angle)
{
        ld si = sin(angle), co = cos(angle), x = trans.fi, y = trans.se;
        return {x * co - y * si, x * si + y * co};
}
pdd dilate(pdd trans, ld fac)
{
        return {trans.fi * fac, trans.se * fac};
}
pair<pdd, pdd> ltangent(pdd p, circle q)
{
        pair<pdd, pdd> res;
        ld r = q.radius;
        ld d2 = dist(p, q.center), d3 = sqrt(d2 * d2 - r * r);
        ld angle = asin(r / d2);
        pdd trans = q.center - p;
        res.fi = p + rotate(dilate(trans, d3 / d2), angle);
        res.se = p + rotate(dilate(trans, d3 / d2), -angle);
        return res;
}
ld area(pdd a, pdd b, pdd c)
{
        return 0.5 * abs(a.fi * b.se + b.fi * c.se + c.fi * a.se - a.se * b.fi - b.se * c.fi - c.se * a.fi);
}
pair<pdd, pdd> itangent(circle p, circle q)
{
        ld r1 = p.radius, r2 = q.radius, d = dist(p.center, q.center);
        pdd trans = q.center - p.center;
        pdd inter = p.center + dilate(trans, (r1 / (r1 + r2)));
        // assert(q.radius < dist(inter, q.center) + EPS);
        return ltangent(inter, q);
}
pair<pdd, pdd> etangent(circle p, circle q)
{
        ld r1 = p.radius, r2 = q.radius, d = dist(p.center, q.center);
        if (abs(r1 - r2) < EPS)
        {
                pdd trans = q.center - p.center;
                pair<pdd, pdd> res = {q.center + rotate(dilate(trans, r1 / d), PI / 2), q.center - rotate(dilate(trans, r1 / d), PI / 2)};
                if (p.center > q.center) swap(res.fi, res.se);
                return res;
        }
        pdd trans = q.center - p.center;
        pdd inter = p.center + dilate(trans, r1 / (r1 - r2));
        return ltangent(inter, q);
}
bool intersects(pdd lo, pdd hi, circle c)
{
        for (int i = 0; i < 100; i++)
        {
                pdd m1 = dilate(lo, 2.0 / 3.0) + dilate(hi, 1.0 / 3.0);
                pdd m2 = dilate(lo, 1.0 / 3.0) + dilate(hi, 2.0 / 3.0);
                ld d1 = dist(c.center, m1), d2 = dist(c.center, m2);
                if (d1 < c.radius - EPS || d2 < c.radius - EPS)
                {
                        return true;
                }
                if (d1 < d2)
                {
                        hi = m2;
                }
                else
                {
                        lo = m1;
                }
        }
        return false;
}
