struct node
{
	int val;
	node *ch[2];
	node()
	{
		val = 0;
		ch[0] = ch[1] = nullptr;
	}
};

node *root[MAXN];

node* build(int w, int L, int R)
{
	node *t = new node();
	if (L == R)
	{
		return t;
	}
	int mid = (L + R) >> 1;
	t -> ch[0] = build(w << 1, L, mid);
	t -> ch[1] = build(w << 1 | 1, mid + 1, R);
	return t;
}
node* update(node *w, int L, int R, int a, int v)
{
	if (a < L || R < a) return w;
	node *t = new node();
	if (L == R)
	{
		t -> val = w -> val + v;
		return t;
	}
	int mid = (L + R) >> 1;
	t -> ch[0] = update(w -> ch[0], L, mid, a, v);
	t -> ch[1] = update(w -> ch[1], mid + 1, R, a, v);
	t -> val = t -> ch[0] -> val + t -> ch[1] -> val;
	return t;
}
int query(node *t, int L, int R, int a, int b)
{
	if (a <= L && R <= b)
	{
		return t -> val;
	}
	int mid = (L + R) >> 1;
	if (b <= mid) return query(t -> ch[0], L, mid, a, b);
	if (mid < a) return query(t -> ch[1], mid + 1, R, a, b);
	return query(t -> ch[0], L, mid, a, b) + query(t -> ch[1], mid + 1, R, a, b);
}
