int N, K;
int s[MAXN];
int child[30][MAXN];
int link[MAXN];
int len[MAXN];
int freq[MAXN];
 
void ins()
{
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
                        node = link[node];
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
