//just helper functions

row mul(row a, int v)
{
    FOR(i, 0, MAGIC)
    {
        a[i] = mul(a[i], v);
    }
    return a;
}
row add(row a, row b)
{
    FOR(i, 0, MAGIC)
    {
        a[i] = add(a[i], b[i]);
    }
    return a;
}
mat mul(mat a, int v)
{
    FOR(i, 0, MAGIC)
    {
        FOR(j, 0, MAGIC)
        {
            a[i][j] = mul(a[i][j], v);
        }
    }
    return a;
}
mat add(mat a, mat b)
{
    FOR(i, 0, MAGIC)
    {
        FOR(j, 0, MAGIC)
        {
            a[i][j] = add(a[i][j], b[i][j]);
        }
    }
    return a;
}
mat mul(mat a, mat b)
{
    mat res;
    FOR(i, 0, SZ(a))
    {
        FOR(j, 0, SZ(b[0]))
        {
            res[i][j] = 0;
	}
    }
    FOR(i, 0, SZ(a))
    {
        FOR(j, 0, SZ(b[0]))
        {
            FOR(k, 0, SZ(b))
            {
                res[i][j] = add(res[i][j], mul(a[i][k], b[k][j]));
            }
        }
    }
    return res;
}
void print(mat m)
{
    FOR(i, 0, SZ(m))
    {
        FOR(j, 0, SZ(m[i]))
        {
            cerr << m[i][j] << ' ';
        }
        cerr << endl;
    }
    return;
}

//solve system of linear equations
    FOR(i, 0, MAGIC)
    {
        if (coef[i][i] == 0)
        {
            int idx = i + 1;
            while(coef[idx][i] == 0) idx++;
            coef[i] = add(coef[i], coef[idx]);
            num[i] = add(num[i], num[idx]);
        }
        int c = dvd(1, coef[i][i]);
        coef[i] = mul(coef[i], c);
        num[i] = mul(num[i], c);
        FOR(j, 0, MAGIC)
        {
            if (j == i) continue;
            int v = sub(0, coef[j][i]);
            coef[j] = add(coef[j], mul(coef[i], v));
            num[j] = add(num[j], mul(num[i], v));
        }
    }

//find inverse of matrix
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
            int idx = i + 1;
            while(m[idx][i] == 0) idx++;
            m[i] = add(m[i], m[idx]);
            res[i] = add(res[i], res[idx]);
        }
        int v = dvd(1, m[i][i]);
        m[i] = mul(m[i], v);
        res[i] = mul(res[i], v);
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
