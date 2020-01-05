        FOR(i, 0, N)
        {
            if (abs(mat[i][i]) < EPS)
            {
                int idx = -1;
                FOR(j, i + 1, R)
                {
                    if (abs(mat[j][i]) > EPS)
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
