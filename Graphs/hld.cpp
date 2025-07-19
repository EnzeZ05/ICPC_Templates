struct HLD{
    int n;
    vector<int> siz, top, dep, fa, in, out, seq;
    vector<vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n): siz(n), top(n), dep(n), fa(n), in(n), out(n), seq(n){
        init(n);
    }

    void init(int n){
        this->n = n;
        cur = 1;
        adj.assign(n, {});
    }

    void add(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int root = 1){
        top[root] = root;
        dep[root] = 0;
        fa[root] = -1;
        dfs1(root);
        dfs2(root);
    }

    void dfs1(int u){
        if(fa[u] != -1){
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        }
        
        siz[u] = 1;
        for(auto &v : adj[u]){
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]){
                swap(v, adj[u][0]);
            }
        }
    }

    void dfs2(int u){
        in[u] = cur++;
        seq[in[u]] = u;
        for(auto v : adj[u]){
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }

    int lca(int u, int v){
        while(top[u] != top[v]){
            if(dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            }
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v){
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k){
        if(dep[u] < k) {
            return -1;
        }
        int d = dep[u] - k;
    
        while(dep[top[u]] > d){
            u = fa[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
    
    bool is_anc(int u, int v){
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rooted_fa(int u, int v) {
        swap(u, v);
        if(u == v){
            return u;
        }
        if(!is_anc(u, v)){
            return fa[u];
        }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rooted_sz(int u, int v) {
        if(u == v) {
            return n;
        }
        if(!is_anc(v, u)) {
            return siz[v];
        }
        return n - siz[rooted_fa(u, v)];
    }
    
    int rooted_lca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
