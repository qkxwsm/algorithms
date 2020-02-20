//solve system of linear equations

FOR(i, 0, N)
{
	if (mat[i][i] < EPS && mat[i][i] > -EPS)
	{
		int idx = -1;
		FOR(j, i + 1, R)
		{
			if (mat[j][i] > 0.1 - EPS || mat[j][i] < -0.1 + EPS)
			{
				idx = j; break;
			}
		}
		FOR(k, 0, N)
		{
			mat[i][k] += mat[idx][k];
		}
		val[i] += val[idx];
	}
	val[i] /= mat[i][i];
	FORD(j, N, i)
	{
		mat[i][j] /= mat[i][i];
	}
	FOR(j, 0, R)
	{
		if (j == i) continue;
		ld co = mat[j][i];
		val[j] -= co * val[i];
		FOR(k, 0, N)
		{
			mat[j][k] -= co * mat[i][k];
		}
	}
}

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
