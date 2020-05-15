//APIO 2014 p1

int N, K;
int s[MAXN];
int child[30][MAXN];
int link[MAXN];
int len[MAXN];
int freq[MAXN];
ll ans;
 
void ins()
{
        //0 has length -1, 1 has length 0
        link[0] = 0; link[1] = 0;
        len[0] = -1; len[1] = 0;
        K = 2;
        int node = 0;
        for (int i = 0; i < N; i++)
        {
                int c = s[i];
                while(node && s[i - 1 - len[node]] != c)
                {
                        node = link[node];
                }
                if (child[c][node])
                {
                        node = child[c][node];
                }
                else
                {
                        len[K] = len[node] + 2;
                        child[c][node] = K;
                        //FIND THE LINK FOR THIS NODE!
                        node = link[node];
                        // cerr << "node = " << node << endl;
                        if (len[K] == 1)
                        {
                                link[K] = 1;
                        }
                        else
                        {
                                while(node && s[i - 1 - len[node]] != c)
                                {
                                        node = link[node];
                                }
                                link[K] = child[c][node];
                        }
                        node = K;
                        K++;
                }
                freq[node]++;
        }
        return;
}
 
int32_t main()
{
        string temps;
        cin >> temps;
        N = temps.length();
        for (int i = 0; i < N; i++)
        {
                s[i] = temps[i] - 'a' + 1;
        }
        ins();
        for (int i = K - 1; i >= 2; i--)
        {
                freq[link[i]] += freq[i];
        }
        for (int i = 2; i < K; i++)
        {
                ckmax(ans, 1ll * freq[i] * len[i]);
        }
        cout << ans << '\n';
	//	cerr << "time elapsed = " << (clock() / (CLOCKS_PER_SEC / 1000)) << " ms" << endl;
	return 0;
}
