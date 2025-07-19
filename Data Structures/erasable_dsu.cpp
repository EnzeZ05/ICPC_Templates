struct DSU {
    vector<int> sz, f;
    vector<array<int, 2>> his;
    
    DSU(int n) : sz(n + 1, 1), f(n + 1) {
        iota(f.begin(), f.end(), 0);
    }
    
    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }
    
    bool merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y){
            return 0;
        }
        if(sz[x] < sz[y]){
            swap(x, y);
        }
        his.push_back({x, y});
        sz[x] += sz[y];
        f[y] = x;
        return 1;
    }
    
    int time(){
        return his.size();
    }
    
    void rollback(int t){
        while (his.size() > t) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            sz[x] -= sz[y];
        }
    }
};