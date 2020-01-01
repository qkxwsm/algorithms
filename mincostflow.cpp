int E = 2, S, T;
int head[MAXN], to[MAXN], link[MAXN], cap[MAXN], par[MAXN];
ll cost[MAXN], dist[MAXN];
 
void addedge(int u, int v, int ca, ll co)
{
    link[E] = head[u];
    to[E] = v;
    cap[E] = ca;
    cost[E] = co;
    head[u] = E;
    E++;
    link[E] = head[v];
    to[E] = u;
    cap[E] = 0;
    cost[E] = -co;
    head[v] = E;
    E++;
}
bool spfa()
{
    FOR(i, 0, T + 1)
    {
        dist[i] = LLINF;
        par[i] = -1;
    }
    dist[S] = 0;
    queue<pll> pq;
    pq.push({0, S});
    while(!pq.empty())
    {
        int u = pq.front().se; ll d = pq.front().fi; pq.pop();
        if (dist[u] != d) continue;
        for (int e = head[u]; e; e = link[e])
        {
            if (cap[e] == 0) continue;
            int v = to[e];
            if (dist[v] <= d + cost[e]) continue;
            dist[v] = d + cost[e];
            par[v] = e;
            pq.push({dist[v], v});
        }
    }
    return (dist[T] < LLINF);
}
pll mcmf()
{
    pll res = MP(0, 0);
    while(true)
    {
        if (!spfa()) break;
        int gain = INF;
        for (int u = T; u != S; u = to[par[u] ^ 1])
        {
            ckmin(gain, cap[par[u]]);
        }
        res.fi += gain;
        for (int u = T; u != S; u = to[par[u] ^ 1])
        {
            cap[par[u]] -= gain;
            cap[par[u] ^ 1] += gain;
            res.se += gain * cost[par[u]];
        }
    }
    return res;
