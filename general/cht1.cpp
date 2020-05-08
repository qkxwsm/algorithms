
    vi opt; opt.PB(0); int iter = 0;
    dp[0] = B[0] * (S - A[0]);
    FOR(i, 1, N + 1)
    {
        while(iter + 1 < SZ(opt) && dp[opt[iter + 1]] + cost(opt[iter + 1], i) <= dp[opt[iter]] + cost(opt[iter], i)) iter++;
        dp[i] = dp[opt[iter]] + cost(opt[iter], i);
        while(SZ(opt) >= 2 && intersect(opt[SZ(opt) - 2], opt.back()) > intersect(opt.back(), i)) opt.pop_back();
        opt.PB(i);
        ckmin(iter, SZ(opt) - 1);
    }
