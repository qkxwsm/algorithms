#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct custom_hash
{
    long long operator()(long long x) const
    {
        x ^= (x >> 15); x *= 998244353;
        return (x ^ (x >> 27));
	//change to 7, 10007, 15 for ints
    }
};

template<class T, class U> using hash_table = gp_hash_table<T, U, custom_hash>;
