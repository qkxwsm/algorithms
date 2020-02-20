//solve system of linear equations
FOR(i, 0, N)
{
	if (mat[i][i] == 0)
	{
		int idx = -1;
		FOR(j, i + 1, R)
		{
			if (mat[j][i] != 0)
			{
				idx = j; break;
			}
		}
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
