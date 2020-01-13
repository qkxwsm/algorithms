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
