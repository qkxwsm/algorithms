 /* KNUTH DP Optimization: dp[i][j] = min(dp[i][k] + dp[k][j]) */
        
        FOR(i, 2, N + 1)
        {
            FOR(j, 0, N - i + 1)
            {
                //find dp[j][j + i]
                dp[j][j + i] = LLINF;
                FOR(k, opt[j][j + i - 1], opt[j + 1][j + i] + 1)
                {
                    if (dp[j][k] + dp[k][j + i] <= dp[j][j + i])
                    {
                        opt[j][j + i] = k;
                        dp[j][j + i] = dp[j][k] + dp[k][j + i];
                    }
                }
                dp[j][j + i] += (pref[j + i] - pref[j]);
            }
        }
        cout << dp[0][N] << '\n';
