struct LCTree{
    struct Line{
        ld k, b;
    };

    vector<Line> p;
    vector<int> tr;

    int n;

    LCTree(int _n) : n(_n), p(4 << __lg(_n)), tr(4 << __lg(_n)) {}

    ld get_y(int id, int x){
        return p[id].k * x + p[id].b;
    }

    void update(int u, int l, int r, int id){
        int mid = (l + r) >> 1;
        if(get_y(id,mid) > get_y(tr[u],mid)){
            swap(id, tr[u]);
        }
        if(get_y(id,l) > get_y(tr[u],l)){
            update(u << 1, l, mid, id);
        }
        if(get_y(id,r) > get_y(tr[u],r)){
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
            return chmax(t, query(u << 1, l, mid, x));
        }
        else{
            return chmax(t, query(u << 1 | 1, mid + 1, r, x));
        }
    }

    ld query(int x){
        return query(1, 1, n, x);
    }
};