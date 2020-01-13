int get(int x)
{
    auto it = prev(s.LB({x, INF}));
    return it -> se;
}
void setrange(int l, int r, int v)
{
    auto it = s.LB({l, -INF});
    int val = (it == s.begin() ? -1 : prev(it) -> se);
    for (; it != s.end() && it -> fi <= r; it = s.erase(it))
    {
        val = it -> se;
    }
    s.insert({l, v});
    if (r + 1 < N && (it == s.end() || it -> fi != r + 1))
    {
        s.insert({r + 1, val});
    }
    return;
}


void ins(int lt, int rt)
{
    auto it = s.LB({lt, INF});
    if (it != s.begin())
    {
        it = prev(it);
        if (it -> fi <= lt && it -> se >= rt)
        {
            return;
        }
        if (it -> se >= lt - 1)
        {
            ckmin(lt, it -> fi);
            upd(it -> fi, it -> se, -1);
            it = s.erase(it);
        }
        else
        {
            it++;
        }
    }
    while(it != s.end() && it -> fi <= rt + 1)
    {
        ckmax(rt, it -> se);
        upd(it -> fi, it -> se, -1);
        it = s.erase(it);
    }
    s.insert({lt, rt});
    upd(lt, rt, 1);
    return;
}
