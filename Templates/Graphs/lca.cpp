struct LCA{
    vector<int> h, w, e, ne, dep;
    vector<vector<int>> fa;
    int n, idx;

    const int depth = 18;

    LCA(int _n){
        n = _n;
        idx = 0;

        dep.resize(n, (int)1e9);
        fa.resize(n);

        ne.resize(n * 2, 0);
        h.resize(n * 2, -1);
        e.resize(n * 2, 0);

        for(int i = 0; i < n; i++){
            fa[i] = vector<int>(depth + 1);
        }
    }

    void add(int u, int v) {
        e[idx] = v, ne[idx] = h[u], h[u] = idx++;
        e[idx] = u, ne[idx] = h[v], h[v] = idx++;
    }

    void bfs(int rt) {
        dep[rt] = 1;
        dep[0] = 0;

        queue<int> q;
        q.push(rt);

        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int i = h[u]; i != -1; i = ne[i]){
                int j = e[i];
                if(dep[j] > dep[u] + 1){
                    dep[j] = dep[u] + 1;

                    q.push(j);
                    fa[j][0] = u;
                    for(int k = 1; k < depth; k++){
                        fa[j][k] = fa[fa[j][k - 1]][k - 1];
                    }
                }
            }
        }
    }

    int lca(int u, int v){
        if(dep[u] < dep[v]) swap(u, v);

        for(int i = depth - 1; i >= 0; i--){
            if(dep[fa[u][i]] >= dep[v]){
                u = fa[u][i];
            }
        }
        if(u == v) return u;

        for(int i = depth - 1; i >= 0; i--){
            if (fa[u][i] != fa[v][i]){
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }
};