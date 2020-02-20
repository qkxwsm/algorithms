//just helper functions

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
FOR(i, 0, N)
{
	if (mat[i][i] == 0)
	{
		int idx = i + 1;
		while(mat[idx][i] == 0) idx++;
		mat[i] = add(mat[i], mat[idx]);
		val[i] = add(val[i], val[idx]);
	}
	int v = dvd(1, mat[i][i]);
	mat[i] = mul(mat[i], v);
	val[i] = mul(val[i], v);
	FOR(j, 0, R)
	{
		if (j == i) continue;
		auto v = mat[j][i]; v = sub(0, v);
		val[j] = mul(val[j], v);
		mat[j] = add(mat[j], mat[i]);
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
