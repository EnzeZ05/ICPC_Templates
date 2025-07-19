vector<int> euler(int n, int m, int src) {
    vector<int> v(m, 0), pt(n);

    for(int i = 0; i < n; ++i){
        pt[i] = h[i];
    }

    vector<int> cycle;
    auto dfs = [&](auto&& self, int u) -> void{
        while(pt[u] != -1){
            int ei = pt[u];
            pt[u] = ne[ei];
            int id = eid[ei];
            if(v[id]){
                continue;
            }
            v[id] = 1;
            self(self, e[ei]);
            cycle.push_back(id);
        }
    };
    dfs(dfs, src);
    reverse(cycle.begin(), cycle.end());

    if((int)cycle.size() != m){
        return {};
    }
    return cycle;
}
