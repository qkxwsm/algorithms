//implements a minqueue using two stacks.

struct minqueue
{
    vpi cur, todo;
    //min up to here, actual value
    void push(int x)
    {
        pii p = {x, x};
        if (!todo.empty())
        {
            ckmin(p.fi, todo.back().fi);
        }
        todo.PB(p);
    }
    void pop()
    {
        if (cur.empty())
        {
            swap(cur, todo);
            reverse(ALL(cur));
            cur[0].fi = cur[0].se;
            FOR(i, 1, SZ(cur)) ckmin(cur[i].fi, cur[i - 1].fi);
        }
        cur.pop_back();
    }
    int query()
    {
        if (!todo.empty())
        {
            if (!cur.empty())
            {
                return min(todo.back().fi, cur.back().fi);
            }
            return todo.back().fi;
        }
        if (!cur.empty())
        {
            return cur.back().fi;
        }
        assert(false);
    }
    void clear()
    {
        cur.clear(); todo.clear();
    }
    bool empty()
    {
        return cur.empty() && todo.empty();
    }
};
