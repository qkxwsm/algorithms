ld mat[MAXN][MAXN];
ld val[MAXN];

FOR(i, 0, N)
{
  FOR(j, i + 1, N)
  {
    //make sure everything is 0.
    ld co = -mat[j][i] / mat[i][i]; 
    //add co * row[i] to row[j];
      FOR(k, 0, N)
      {
        mat[j][k] += mat[i][k] * co;
      }
      val[j] += val[i] * co;
  }
}
FORD(i, N, 0)
{
  FORD(j, i, 0)
  {
    ld co = -mat[j][i] / mat[i][i];
    FOR(k, 0, N)
    {
      mat[j][k] += mat[i][k] * co;
    }
    val[j] += val[i] * co;
  }
}
