int n, m, sqn;
int dfn[N], low[N], fu[N], fw[N], fe[N], cnt;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int fa[N][20], dep[N], d[N];
int s[N], stot[N];
int x, y;

void add(int h[], int u, int v, int c){
    e[idx] = v, w[idx] = c, ne[idx] = h[u], h[u] = idx++;
}

void build(int x, int y, int z){
    int sum = z;
    for(int k = y; k != x; k = fu[k]){
        s[k] = sum;
        sum += fw[k];
    }
    
    s[x] = stot[x] = sum;
    add(h2, x, ++sqn, 0);
    
    for(int k = y; k != x; k = fu[k]){
        stot[k] = sum;
        add(h2, sqn, k, chmin(s[k], sum - s[k]));
    }
}

void tarjan(int u, int fa){
    dfn[u] = low[u] = ++cnt;
    for(int i = h1[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(!dfn[j]){
            fu[j] = u, fw[j] = w[i], fe[j] = i;
            tarjan(j, i);
            low[u] = chmin(low[u], low[j]);
            if(dfn[u] < low[j]){ 
                add(h2, u, j, w[i]);
            }
        }
        else if(i != (fa ^ 1)){
            low[u] = chmin(low[u], dfn[j]);
        }
    }
    
    for(int i = h1[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(dfn[u] < dfn[j] && fe[j] != i){
            build(u, j, w[i]);
        }
    }
}

void dfs(int u, int anc){
    dep[u] = dep[anc] + 1;
    fa[u][0] = anc;
    for(int k = 1; k < 20; k++){
        fa[u][k] = fa[fa[u][k - 1]][k - 1];
    }
    
    for(int i = h2[u]; i != -1; i = ne[i]){
        int j = e[i];
        d[j] = d[u] + w[i];
        dfs(j, u);
    }
}

int lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    for(int k = 19; k >= 0; k--){
        if(dep[fa[u][k]] >= dep[v]){
            u = fa[u][k];
        }
    }
    if(u == v) return u;
    
    for(int k = 19; k >= 0; k--){
        if(fa[u][k] != fa[v][k]){
            u = fa[u][k];
            v = fa[v][k];
        }
    }
    x = u, y = v;
    return fa[u][0];
}

/*
    sqn = n;
    tarjan(1, -1);
    dfs(1, -1);

    for(int i = 0; i < Q; i++){ 分类讨论距离
        int u, v;
        scanf("%d%d", &u, &v);
        int p = lca(u, v);
        if(p <= n){
            printf("%d\n", d[u] + d[v] - d[p] * 2);
        }
        else{
            int ysy = d[u] - d[x], qwq = d[v] - d[y];
            int l = abs(s[x] - s[y]);
            int mid = min(l, stot[x] - l);
            printf("%d\n", ysy + qwq + mid);
        }
    }
*/
