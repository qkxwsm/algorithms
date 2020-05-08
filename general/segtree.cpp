/* Segtree, lazy with range += v, queries max */

int seg[3 * MAXN], lazy[3 * MAXN];

void push(int w, int L, int R)
{
    if (lazy[w] == 0) return;
    seg[w] += lazy[w];
    if (L != R)
    {
        lazy[w << 1] += lazy[w];
        lazy[w << 1 | 1] += lazy[w];
    }
    lazy[w] = 0;
    return;
}
void update(int w, int L, int R, int a, int b, int v)
{
    push(w, L, R);
    if (b < L || R < a) return;
    if (a <= L && R <= b)
    {
        lazy[w] += v;
        push(w, L, R);
        return;
    }
    int mid = (L + R) >> 1;
    update(w << 1, L, mid, a, b, v);
    update(w << 1 | 1, mid + 1, R, a, b, v);
    seg[w] = max(seg[w << 1], seg[w << 1 | 1]);
}
int query(int w, int L, int R, int a, int b)
{
    push(w, L, R);
    if (a <= L && R <= b) return seg[w];
    int mid = (L + R) >> 1;
    if (b <= mid) return query(w << 1, L, mid, a, b);
    if (mid < a) return query(w << 1 | 1, mid + 1, R, a, b);
    return max(query(w << 1, L, mid, a, b), query(w << 1 | 1, mid + 1, R, a, b));
}
