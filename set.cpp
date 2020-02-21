struct cmp
{
    bool operator() (const int a, const int b) const
    {
        return eval(a) < eval(b);
    }
};

set<int, cmp> segs;
