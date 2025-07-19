vector<int> g[N];

ll f[N], d[N];
int n, m;

void bellman_ford(){
    for(int i = 1; i <= n; i++){
        f[i] = INF;
    }

    f[1] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= n; j++){
            d[j] = f[j];
        }
        for(int j = 0; j < m; j++){
            int u = g[j][0], v = g[j][1], w = g[j][2];
            f[v] = chmin(f[v], chmax(0ll, d[u] + w));
        }
    }
}
