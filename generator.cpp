#include <bits/stdc++.h>

using namespace std;

template<class T, class U>
void ckmin(T &a, U b)
{
    if (a > b) a = b;
}

template<class T, class U>
void ckmax(T &a, U b)
{
    if (a < b) a = b;
}

random_device rd;
mt19937 rng(rd());

template<class T>
T randomize(T mod)
{
	return uniform_int_distribution<T>(0, mod - 1)(rng);
}
long double randomize()
{
    return uniform_real_distribution<long double>(0.0, 1.0)(rng);
}

#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define SZ(x) ((int) (x).size())
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (auto i = (a); i < (b); i++)
#define FORD(i, a, b) for (auto i = (a) - 1; i >= (b); i--)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vd;
typedef vector<pii> vpi;
typedef vector<pll> vpl;

void print(vpi v, int flag = 1)
{
    for (pii p : v)
    {
        cout << p.fi + flag << ' ' << p.se + flag << '\n';
    }
}
void print(vi v, int flag = 0)
{
    FOR(i, 0, SZ(v))
    {
        cout << v[i] + flag << " \n"[i == SZ(v) - 1];
    }
}
void print(vector<ld> v)
{
    FOR(i, 0, SZ(v))
    {
        cout << v[i] << " \n"[i == SZ(v) - 1];
    }
}

template<class T>
vector<T> shuffle(vector<T> v)
{
    FOR(i, 1, SZ(v))
    {
        swap(v[i], v[randomize(i + 1)]);
    }
    return v;
}
vi genarray(int n, int mx)
{
    vi res(n);
    FOR(i, 0, n)
    {
        res[i] = randomize(mx);
    }
    return res;
}
vpi genpair(int n, int mx)
{
    vpi res(n);
    FOR(i, 0, n)
    {
        res[i].fi = randomize(mx); res[i].se = randomize(mx);
    }
    return res;
}
vd genprob(int n)
{
    vd res(n);
    FOR(i, 0, n)
    {
        res[i] = randomize();
    }
    return res;
}
vi genperm(int n)
{
    vi res(n);
    iota(ALL(res), 0);
    res = shuffle(res);
    return res;
}
vpi gentree(int n)
{
    vpi res(n - 1);
    FOR(i, 1, n)
    {
        res[i - 1] = {randomize(i), i};
    }
    vi go = genperm(n);
    FOR(i, 0, n - 1)
    {
        res[i].fi = go[res[i].fi];
        res[i].se = go[res[i].se];
    }
    res = shuffle(res);
    return res;
}
vpi gengraph(int n, int m)
{
    vpi res = gentree(n);
    set<pii> s;
    for (auto p : res)
    {
        s.insert(p);
        s.insert({p.se, p.fi});
    }
    FOR(i, 0, m - (n - 1))
    {
        int x, y;
        do
        {
            x = randomize(n); y = randomize(n);
        }
        while(x == y || s.count({x, y}));
        s.insert({x, y});
        s.insert({y, x});
        res.PB({x, y});
    }
    return res;
}
vpi genanygraph(int n, int m)
{
    vpi res;
    set<pii> s;
    FOR(i, 0, m)
    {
        int x, y;
        do
        {
            x = randomize(n); y = randomize(n);
            if (x > y) swap(x, y);
        }
        while(x == y || s.count({x, y}));
        s.insert({x, y});
        res.PB({x, y});
    }
    return res;
}

int32_t main()
{
    cout << fixed << setprecision(6);
    cerr << fixed << setprecision(4);
    ios_base::sync_with_stdio(false); cin.tie(0);
    print(genpair(7, 13));
    // print(gentree(13));
    return 0;
}
