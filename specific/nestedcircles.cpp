/* finds the underlying structure for nested circles */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

random_device rd;
mt19937 rng(rd());

template<class T>
T randomize(T mod)
{
    return uniform_int_distribution<T>(0, mod - 1)(rng);
}

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
typedef vector<pii> vpi;
typedef vector<pll> vpl;

const int MAXN = 100013;
const ll LLINF = 3e18;

struct circle
{
    pll center;
    ll radius;
    int id;
};

ll dist(pll a, pll b)
{
    return (a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se);
}
bool inside(circle a, circle b)
{
    //checks if circle a is inside circle b
    return (a.radius <= b.radius && dist(a.center, b.center) < (b.radius - a.radius) * (b.radius - a.radius));
}

struct arc
{
    circle c;
    bool typ;
    bool operator < (arc a) const
    {
        if (c.id == a.c.id)
        {
            return !typ && (a.typ);
        }
        if (inside(c, a.c)) //it depends on whether a is the upper or not. if a is upper, then c is <.
        {
            return a.typ;
        }
        else if (inside(a.c, c))
        {
            return !typ;
        }
        return c.center.se < a.c.center.se;
    }
};

struct event
{
    pll p;
    bool typ;
    arc a;
};


int N, T;
circle arr[MAXN];
set<arc> s;
int parent[MAXN];
vector<event> events;
int st[MAXN], ft[MAXN];
vi edge[MAXN];
ll ans[MAXN];

ll dfs(int u, int t)
{
	//how much area did u finish painting in subtree[u] by time t? since then ur gonna paint parent at time t
	if (u <= t)
	{
		ll res = arr[u].radius * arr[u].radius;
		for (int v : edge[u])
		{
			if (v == parent[u]) continue;
			res -= dfs(v, min(u, v));
		}
		ans[u] = res;
		return arr[u].radius * arr[u].radius;
	}
	else
	{
		ans[u] = 0;
		ll res = 0;
		for (int v : edge[u])
		{
			if (v == parent[u]) continue;
			res += dfs(v, min(t, v));
		}
		return res;
	}
}

int32_t main()
{
    cout << fixed << setprecision(12);
    cerr << fixed << setprecision(4);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    FOR(i, 0, N)
    {
        cin >> arr[i].center.fi >> arr[i].center.se >> arr[i].radius; arr[i].id = i;
        event cur;
        cur.a.c = arr[i];
        cur.typ = true;
        cur.p = {arr[i].center.fi - arr[i].radius, arr[i].center.se};
        cur.a.typ = false;
        events.PB(cur);
        cur.a.typ = true;
        events.PB(cur);
        cur.typ = false;
        cur.p = {arr[i].center.fi + arr[i].radius, arr[i].center.se};
        cur.a.typ = false;
        events.PB(cur);
        cur.a.typ = true;
        events.PB(cur);
    }
    sort(ALL(events), [&](event a, event b)
    {
        if (a.p.fi != b.p.fi)
        {
            return a.p.fi < b.p.fi;
        }
        if (a.typ != b.typ) //deletes come before inserts.
        {
            return !a.typ;
        }
        if (a.p != b.p) //do it in order of y.
        {
            return a.p < b.p;
        }
        return a.a < b.a;
    });
    for (event e : events)
    {
        //if it's an upper arc, it's the parent. if it's the lower arc, its parent is the parent. if it's nothign, no parent.
        if (e.typ) //insert.
        {
            if (!e.a.typ) //find my parent.
            {
                //who's my parent?
                auto it = s.LB(e.a);
                if (it == s.begin())
                {
                    parent[e.a.c.id] = N;
                }
                else
                {
                    it = prev(it);
                    if (it -> typ) //upper arc.
                    {
                        parent[e.a.c.id] = parent[it -> c.id];
                    }
                    else
                    {
                        parent[e.a.c.id] = it -> c.id;
                    }
                }
            }
            s.insert(e.a);
        }
        else
        {
            s.erase(e.a);
        }
    }
    for (int i = 0; i < N; i++)
	{
		if (parent[i] != N) edge[parent[i]].PB(i);
	}
	for (int i = 0; i < N; i++)
	{
		if (parent[i] == N) dfs(i, i);
	}
	for (int i = 0; i < N; i++)
	{
		cout << ans[i] << '\n';
	}
    return 0;
}
