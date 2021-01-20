int sparse[20][MAXN];

int qry(int l, int r)
{
    int sz = 31 - __builtin_clz(r - l + 1);
    return max(sparse[sz][l], sparse[sz][r - (1 << sz) + 1]);
}

    FOR(i, 0, N)
    {
        sparse[0][i] = arr[i];
    }
    FOR(i, 1, 20)
    {
        FOR(j, 0, N - (1 << i) + 1)
        {
            sparse[i][j] = max(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
        }
    }
