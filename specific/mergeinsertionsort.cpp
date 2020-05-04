vi sortnums(vi v)
{
    //merge-insertion sort to sort v numbers.
    // sort(ALL(v), ask); return v;
    if (SZ(v) <= 1) return v;
    map<int, int> match;
    vi t;
    for (int i = 1; i < SZ(v); i += 2)
    {
        bool b = ask(v[i - 1], v[i]);
        if (!b) swap(v[i - 1], v[i]);
        t.PB(v[i]);
        match[v[i]] = v[i - 1];
    }
    t = sortnums(t);
    vi res = t;
    res.insert(res.begin(), match[t[0]]);
    int pw = 4, l = 1, r = 3;
    while(l < SZ(t))
    {
        int j = min(pw, SZ(res)) - 1;
        FORD(i, min(r, SZ(t)), l)
        {
            while (res[j] != t[i])
            {
                j--;
            }
            res.insert(LB(res.begin(), res.begin() + j, match[t[i]], ask), match[t[i]]);
        }
        pw <<= 1;
        l = r; r = pw - r;
    }
    if (SZ(v) & 1)
    {
        res.insert(LB(ALL(res), v.back(), ask), v.back());
    }
    return res;
}
