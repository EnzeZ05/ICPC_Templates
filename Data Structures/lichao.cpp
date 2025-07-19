struct LCTree{
    struct Line{
        ld k, b;
    };
 
    vector<Line> p;
    vector<int> tr;
 
    int n, id;

    LCTree(){}
 
    LCTree(int _n) : n(_n), p(4 << __lg(_n), {0, INF}), tr(4 << __lg(_n)) {
        id = 0;
    }
 
    ld get_y(int id, int x){
        return p[id].k * x + p[id].b;
    }
 
    void add(ld k, ld b){
        p[++id] = {k, b};
        update(id);
    }
 
    void update(int u, int l, int r, int id) {
        if(l == r) {
            if(get_y(id, l) < get_y(tr[u], l)){
                tr[u] = id;
            }
            return;
        }
        
        int mid = (l + r) / 2;
        bool left = get_y(id, l) < get_y(tr[u], l);
        bool m = get_y(id, mid) < get_y(tr[u], mid);
        if(m){
            swap(id, tr[u]);
        }
        if(left != m){
            update(u << 1, l, mid, id);
        }
        else{
            update(u << 1 | 1, mid + 1, r, id);
        }
    }

 
    void update(int id){
        update(1, 1, n, id);
    }
 
    ld query(int u, int l, int r, int x){
        if(l == r) return get_y(tr[u], x);
        int mid = l + r >> 1;
        ld t = get_y(tr[u], x);
        if(x <= mid){
            return chmin(t, query(u << 1, l, mid, x));
        }
        else{
            return chmin(t, query(u << 1 | 1, mid + 1, r, x));
        }
    }
 
    ld query(int x){
        return query(1, 1, n, x);
    }
};
