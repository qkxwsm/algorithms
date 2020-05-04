	vi bucket, lis;
	FOR(i, 0, N)
	{
		if (!lis.empty() && eq(lis.back(), i))
		{
			bucket.PB(i);
			continue;
		}
		else
		{
			lis.PB(i);
			if (!bucket.empty())
			{
				lis.PB(bucket.back());
				bucket.pop_back();
			}
		}
	}
  int cand = lis.back();
	//any two adjacent elements in lis are different!
	while(!lis.empty())
	{
		int x = lis.back();
		if (eq(x, cand))
		{
      if (SZ(lis) == 1)
      {
        bucket.PB(lis.back());
        lis.pop_back();
      }
      else
      {
			  lis.pop_back();
			  if (!lis.empty()) lis.pop_back();
      }
		}
		else
		{
			lis.pop_back();
			bucket.pop_back();
		}
	}
	cout << (bucket.empty() ? -1 : bucket.back()) << '\n';
