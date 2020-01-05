struct node
{
	//////// VARIABLES
	node *p, *c[2]; // parent, children
	// node* extra; // extra cycle node
	bool flip = 0; // subtree flipped or not
	int val; // value in node, # nodes in subtree

	// int vir = 0; stores sum of virtual children
	node(int v) {
		p = c[0] = c[1] = NULL;
		val = v; calc();
	}
	// friend int getSz(node* x) { return x?x->sz:0; }
	void prop() { // lazy prop
		if (!flip) return;
		swap(c[0],c[1]); FOR(i, 0, 2) if (c[i]) c[i]->flip ^= 1;
		flip = 0;
	}
	void calc() { // recalc vals
		FOR(i, 0, 2) if (c[i]) c[i]->prop();
		// sz = 1+getSz(c[0])+getSz(c[1]);
	}
	//////// SPLAY TREE OPERATIONS
	int dir() {
		if (!p) return -2;
		FOR(i, 0, 2) if (p->c[i] == this) return i;
		return -1; // p is path-parent pointer,
		// so not in current splay tree
	}
	bool isRoot() { return dir() < 0; }
	// test if root of current splay tree
	friend void setLink(node *x, node *y, int d) {
		if (y) y->p = x;
		if (d >= 0) x->c[d] = y;
	}
	void rot() { // assume p and p->p propagated
		assert(!isRoot()); int x = dir(); node* pa = p;
		setLink(pa->p, this, pa->dir());
		setLink(pa, c[x^1], x);
		setLink(this, pa, x^1);
		pa->calc(); calc();
	}
	void splay() {
		while (!isRoot() && !p->isRoot()) {
			p->p->prop(), p->prop(), prop();
			dir() == p->dir() ? p->rot() : rot();
			rot();
		}
		if (!isRoot()) p->prop(), prop(), rot();
		prop();
	}
	//////// LINK CUT TREE BASE OPERATIONS
	void access() { // bring this to top of tree
		for (node *v = this, *pre = nullptr; v; v = v->p) {
			v->splay();
			// if (pre) v->vir -= pre->sz;
			// if (v->c[1]) v->vir += v->c[1]->sz;
			v->c[1] = pre; v->calc();
			pre = v;
			// v->sz should remain the same if using vir
		}
		splay(); // left subtree of this is now path to root
		assert(!c[1]); // right subtree is empty
	}
	void makeRoot() { access(); flip ^= 1; }
	void set(int v) { splay(); val = v; calc(); }
	// change val in node,
	// splay suffices instead of access because
	// it doenode*'t affect values in nodes above it
	//////// LINK CUT TREE QUERIES
	friend node* lca(node* x, node* y) {
		if (x == y) return x;
		x->access(), y->access(); if (!x->p) return NULL;
		// access at y did not affect x
		// so they must not be connected
		x->splay(); return x->p ? x->p : x;
	}
	friend bool connected(node* x, node* y) { return lca(x,y); }
	// LCA is null if not connected
	// int distRoot() { access(); return getSz(c[0]); }
	// # nodes above
	node* getRoot() { // get root of LCT component
		access(); auto a = this;
		while (a->c[0]) a = a->c[0], a->prop();
		a->access(); return a;
	}
	/*node* dfs(int b) {
		int z = getSz(c[0]);
		if (b < z) return c[0]->dfs(b);
		if (b == z) { access(); return this; }
		return c[1]->dfs(b-z-1);
	}*/
	//////// LINK CUT TREE MODIFICATIONS
	friend bool link(node* x, node* y) { // make x parent of y
		if (connected(x,y)) return 0; // don't induce cycle
		// y->access(); assert(!y->c[0]);
		y->makeRoot(); // if you want to ensure link succeeds
		y->p = x;
		// x->access(); x->sz += y->sz; x->vir += y->sz;
		return 1;
	}
	friend bool cut(node* y) { // cut y from its parent
		y->access(); if (!y->c[0]) return 0;
		y->c[0]->p = NULL; y->c[0] = NULL;
		y->calc(); return 1;
	}
	friend bool cut(node* x, node* y) { // if x, y adjacent in tree
		x->makeRoot(); y->access();
		if (y->c[0] != x || x->c[0] || x->c[1]) return 0;
		// splay tree with y should not contain anything besides x
		assert(cut(y)); return 1;
	}
};
