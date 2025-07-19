struct Kruskal{
    vector<int> h, w, e, ne, dep, node;
    vector<vector<int>> fa, kr;
    int n, idx, t;

    const int depth = 21;

    Kruskal(int _n){
        n = _n;
        idx = 0;

        dep.resize(n * 4 + 1, (int)1e9);
        fa.resize(n * 4 + 1);

        ne.resize(n * 4 + 1, 0);
        h.resize(n * 4 + 1, -1);
        e.resize(n * 4 + 1, 0);
        w.resize(n * 4 + 1, 0);
        
        node.resize(n * 4 + 1, 0);

        for(int i = 0; i <= n * 4; i++){
            fa[i] = vector<int>(depth + 1);
            node[i] = i;
        }
    }

    int find(int x) {
        return x == node[x] ? x : node[x] = find(node[x]);
    }

    void build(int u, int v) {
        e[idx] = v, ne[idx] = h[u], h[u] = idx++;
        e[idx] = u, ne[idx] = h[v], h[v] = idx++;
    }

    void kruskal(){
        for(int k = n, i = 1; i <= kr.size(); i++){
            int du = find(kr[i - 1][0]), dv = find(kr[i - 1][1]);
        
            if(du != dv){
                node[du] = node[dv] = ++k;
                w[k] = kr[i - 1][2];
                build(k, du);
                build(k, dv);
                t = k;

                if(k == 2 * n - 1){
                    break;
                }
            }
        }
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
                    for(int k = 0; k < depth; k++){
                        fa[j][k + 1] = fa[fa[j][k]][k];
                    }
                }
            }
        }
    }

    int lca(int u, int v){
        if(find(u) != find(v)) return -1;
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

//自己定义sort 第三关键字