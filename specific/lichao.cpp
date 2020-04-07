//Li Chao Tree. Queries max.

struct node
{
    node *ch[2];
    pll p;
    node(pll pr)
    {
        p = pr;
        ch[0] = nullptr;
        ch[1] = nullptr;
    }
};

node *root;

ll f(ll x, pll p)
{
    return p.fi * x + p.se;
}
node* update(node *w, int L, int R, pll p)
{
    if (!w)
    {
        w = new node(p);
        return w;
    }
    if (L == R)
    {
        if (f(L, p) > f(L, w -> p)) w -> p = p;
        return w;
    }
    int mid = (L + R) >> 1;
    if (p.fi == w -> p.fi)
    {
        if (p.se > w -> p.se)
        {
            w -> p = p;
        }
        return w;
    }
    if (p.fi < w -> p.fi)
    {
        swap(w -> p, p);
    }
    //p.fi > stor[w].fi
    if (f(mid + 1, p) > f(mid + 1, w -> p))
    {
        swap(w -> p, p);
        w -> ch[0] = update(w -> ch[0], L, mid, p);
    }
    else
    {
        w -> ch[1] = update(w -> ch[1], mid + 1, R, p);
    }
    return w;
}
ll query(node *w, int L, int R, int a)
{
    ll res = f(a, w -> p);
    if (L == R) return res;
    int mid = (L + R) >> 1;
    if (a <= mid)
    {
        if (w -> ch[0]) ckmax(res, query(w -> ch[0], L, mid, a));
    }
    else
    {
        if (w -> ch[1]) ckmax(res, query(w -> ch[1], mid + 1, R, a));
    }
    return res;
}
void ins(ll x, ll y)
{
    root = update(root, 0, (1 << 30) - 1, {x, y});
}
ll qry(ll x)
{
    ll res = query(root, 0, (1 << 30) - 1, x);
    return res;
}
