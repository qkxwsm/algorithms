vi manacher(vi str)
{
	vi s(2 * SZ(str) + 1);
	FOR(i, 0, SZ(str))
	{
		s[2 * i + 1] = str[i];
	}
	vi res(SZ(s));
	int l = 1, r = 1;
	FOR(i, 1, SZ(s))
	{
		res[i] = min(res[l + r - i], r - i);
		while(i + res[i] + 1 < SZ(s) && i - res[i] - 1 >= 0 && s[i + res[i] + 1] == s[i - res[i] - 1]) res[i]++;
		if (i + res[i] > r)
		{
			l = i - res[i];
			r = i + res[i];
		}
	}
	return res;
}
