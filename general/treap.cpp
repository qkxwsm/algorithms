struct node
{
	int val, pri, subt;
	bool rev;
	node *ch[2];
	node(int x)
	{
		val = x;
		pri = rand() % INF;
		subt = 1;
		rev = false;
	}
};

typedef pair<node*, node*> pnn;
void prop(node *t)
{
	if (!t) return;
	if (!(t -> rev)) return;
	if (t -> ch[0]) t -> ch[0] -> rev ^= true;
	if (t -> ch[1]) t -> ch[1] -> rev ^= true;
	swap(t -> ch[0], t -> ch[1]);
	t -> rev = false;
	return;
}
void pull(node *t)
{
	if (!t) return;
	t -> subt = 1;
	if (t -> ch[0]) t -> subt += t -> ch[0] -> subt;
	if (t -> ch[1]) t -> subt += t -> ch[1] -> subt;
	return;
}
node *merge(node *l, node *r)
{
	prop(l); prop(r);
	if (!l) return r;
	if (!r) return l;
	if (l -> pri > r -> pri)
	{
		l -> ch[1] = merge(l -> ch[1], r);
		pull(l); return l;
	}
	else
	{
		r -> ch[0] = merge(l, r -> ch[0]);
		pull(r); return r;
	}
}
pnn split(node *t, int v)
{
	//exactly v values go to the left
	if (!t) return {t, t};
	prop(t);
	int cur = (t -> ch[0] ? t -> ch[0] -> subt : 0) + 1;
	if (cur <= v)
	{
		pnn p = split(t -> ch[1], v - cur);
		t -> ch[1] = p.fi; pull(t);
		return {t, p.se};
	}
	else
	{
		pnn p = split(t -> ch[0], v);
		t -> ch[0] = p.se; pull(t);
		return {p.fi, t};
	}
}
