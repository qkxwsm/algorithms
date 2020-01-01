//untested

struct node
{
	node *ch[2], *p;
	bool flip;
	int id;
	int sdat, dat;	//dist sum of int and its own int...
	int dist;
	node()
	{
		ch[0] = ch[1] = p = NULL;
		flip = 0;
		id = 0;
		sdat = 0;
		dat = 0;
		dist = 1;
	}
};
 
node lct[MAXN];
 
int getdir(node *t)
{
	if (!(t -> p)) return -1;
	FOR(i, 0, 2)
	{
		if (t == (t -> p) -> ch[i]) return i;
	}
	return -1;
}
bool isroot (node *t)
{
	return (getdir(t) == -1);
}
void setc (node *t, node *c, int dir)
{
	t -> ch[dir] = c;
	if (c) c -> p = t;
}
void push (node *t)
{
	if (!(t -> flip)) return;
	swap(t -> ch[0], t -> ch[1]);
	if (t -> ch[0]) t -> ch[0] -> flip ^= 1;
	if (t -> ch[1]) t -> ch[1] -> flip ^= 1;
	t -> flip = false;
}
void pull (node *t)
{
	t -> sdat = (t -> ch[0] ? t -> ch[0] -> sdat : 0) + t -> dat + (t -> ch[1] ? t -> ch[1] -> sdat : 0);
	t -> dist = (t -> ch[0] ? t -> ch[0] -> dist : 0) + 1 + (t -> ch[1] ? t -> ch[1] -> dist : 0);
}
void rot (node *t)
{
	node *p = t -> p, *g = p -> p;
	bool d = getdir(t);
	if (!isroot(p))
	{
		g -> ch[getdir(p)] = t;
	}
	setc(p, t -> ch[!d], d);
	pull(p);
	t -> p = g;
	setc(t, p, !d);
	pull(t);
}
void splay (node *t)
{
	while (!isroot(t))
	{
		node *p = t -> p;
		if (!isroot(p))
		{
			push(p -> p);
		}
		push(p);
		push(t);
		if (!isroot(p))
		{
			rot(getdir(t) == getdir(p) ? p : t);
		}
		rot(t);
	}
	push(t);
}
node* expose (node *u, bool flag = false)
{
	if (!u) return u;
	node *t = u, *v = nullptr;
	while(u)
	{
		splay(u);
		u -> ch[1] = v;
		v = u;
		u = u -> p;
	}
	splay(t);
	if (flag)
	{
		t -> flip = true;
		push(t);
		splay(t);
	}
	assert(t -> p == NULL);
	return v;
}
bool conn (node *u, node *v)
{
	if (u == v) return true;
	expose(u);
	expose(v);
	if (!(u -> p)) return false;
	return true;
}
void link (node *u, node *v)
{
	expose(u);
	expose(v, 1);
	v -> ch[0] = u;
	u -> p = v;
}
void cut(node *u)
{
	expose(u);
	u -> ch[0] -> p = nullptr;
	u -> ch[0] = nullptr;
	return;
}
void update (node *u, int val)
{
	expose(u);
	u -> dat = val;
	pull(u);
}
int depth(node *u)
{
	expose(u);
	int res = 0;
	while(u)
	{
		res += (u -> ch[0] ? u -> ch[0] -> dist : 0) + 1;
		u = u -> p;
	}
	return res;
}
node* ancestor(node *u, int k)
{
	k++;
	expose(u);
	while(true)
	{
		int siz = (u -> ch[0] ? u -> ch[0] -> dist : 0) + 1;
		if (k > siz)
		{
			k -= siz;
			u = u -> p;
			continue;
		}
		while(true)
		{
			siz = (u -> ch[1] ? u -> ch[1] -> dist : 0) + 1;
			if (k == siz) break;
			if (k < siz)
			{
				u = u -> ch[1];
			}
			else if (k > siz)
			{
				k -= siz;
				u = u -> ch[0];
			}
		}
		splay(u);
		return u;
	}
}
node* lca(node *u, node *v)
{
	expose(u);
	return expose(v);
}
node* find_root(node *u)
{
	expose(u);
	while(u -> ch[0])
	{
		u = u -> ch[0];
	}
	splay(u);
	return u;
}
