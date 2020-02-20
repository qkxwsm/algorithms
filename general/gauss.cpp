mat getinv(mat m)
{
    mat res;
    FOR(i, 0, SZ(res))
    {
        FOR(j, 0, SZ(res))
        {
            res[i][j] = 0;
        }
        res[i][i] = 1;
    }
    FOR(i, 0, SZ(m))
    {
        if (m[i][i] == 0)
        {
            FOR(j, i + 1, SZ(m))
            {
                if (m[j][i] != 0)
                {
                    m[i] = add(m[i], m[j]);
                    res[i] = add(res[i], res[j]);
                    break;
                }
            }
        }
        print(m); print(res);
        int v = dvd(1, m[i][i]);
        m[i] = mul(m[i], v);
        res[i] = mul(res[i], v);
        print(m); print(res);
        FOR(j, 0, SZ(m))
        {
            if (i == j) continue;
            int x = m[j][i]; x = sub(0, x);
            m[j] = add(m[j], mul(m[i], x));
            res[j] = add(res[j], mul(res[i], x));
        }
    }
    return res;
}
