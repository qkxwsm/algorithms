//push, pop, find min/max in a queue.
struct minqueue
{
    vpi cur, todo;
    //each of these vectors is actually two stacks.
    //stores pair (min up to here, actual value)
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
            FOR(i, 1, SZ(cur))
            {
                cur[i].fi = min(cur[i - 1].fi, cur[i].se);
            }
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
