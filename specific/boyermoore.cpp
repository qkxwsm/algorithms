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
	//any two adjacent elements in lis are different!
	while(!bucket.empty() && !lis.empty())
	{
		int x = lis.back(), T = bucket.back();
		if (eq(x, T))
		{
			lis.pop_back();
			if (!lis.empty()) lis.pop_back();
		}
		else
		{
			lis.pop_back();
			bucket.pop_back();
		}
	}
	cout << (bucket.empty() ? -1 : bucket.back()) << '\n';
