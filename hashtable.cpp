#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct custom_hash
{
	template<class T>
	T operator()(T v) const
	{
		v = (v ^ (v >> 15)) * 69;
		return (v ^ (v >> 7));
	}
};

template<class T, class U> using hash_table = gp_hash_table<T, U, custom_hash>;
