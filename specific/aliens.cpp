check(0);
ckmin(M, taken[N + 1]);
ll lo = 0, hi = INF;
while(hi > lo)
{
  ll mid = (hi + lo + 1) >> 1;
  check(mid);
  if (taken[N + 1] >= M) lo = mid;
  else hi = mid - 1;
}
//lo is the highest cost such that we take >= M.
check(lo);
ll res1 = dp[N + 1]; int take1 = taken[N + 1]; //use take1 segments, each of cost lo, final cost res1
check(lo + 1);
ll res2 = dp[N + 1]; int take2 = taken[N + 1];
ll val1 = res1 - take1 * lo, val2 = res2 - take2 * (lo + 1);
ans = val1 + (val2 - val1) / (take1 - take2) * (take1 - M);
