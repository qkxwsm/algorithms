void move(int lt, int rt)
{
    if (hi < lt - 2)
    {
        move(hi, hi - 1);
        lo = lt;
        hi = lt - 1;
    }
    else if (lo > rt + 2)
    {
        move(lo + 1, lo);
        lo = rt + 1;
        hi = rt;
    }
    while(hi < rt)
    {
        hi++;
        //do whatever
    }
    while(lo > lt)
    {
        lo--;
        //do whatever
    }
    while(hi > rt)
    {
        //do whatever
        hi--;
    }
    while(lo < lt)
    {
        //do whatever
        lo++;
    }
}
