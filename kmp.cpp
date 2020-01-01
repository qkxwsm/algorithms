vi kmp(vi str)
{
	vi res(SZ(str));
	res[0] = 0;
	FOR(i, 1, SZ(str))
	{
		int j = res[i - 1];
		while(j && str[j] != str[i])
		{
			j = res[j - 1];
		}
		res[i] = j + (str[i] == str[j]);
	}
	return res;
}
