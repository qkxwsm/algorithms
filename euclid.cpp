ll modinv(ll a, ll m)
{
    //ax = 1 mod m
    if (a == 1) return 1;
    ll y = modinv(m % a, a);
    ll k = m / a, j = m % a;
    ll res = -((j * y - 1) / a) - k * y;
    res %= m; res += m;
    return res;
}
