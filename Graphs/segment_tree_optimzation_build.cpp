const int N = (int)2e6 + 1, M = N * 2;
int h[N], e[M], ne[M], idx;
ll w[M];

void add(int u, int v, ll c){
    e[idx] = v, w[idx] = c, ne[idx] = h[u], h[u] = idx++;
}

struct SegTree {
    const int n;
    
    vector<int> in, out;
    int cnt;

    SegTree(int n) : n(n), in(4 << __lg(n)), out(4 << __lg(n)){
        function<void(int, int, int)> build = [&](int u, int l, int r){
            if(l == r){
                out[u] = l;
                in[u] = l;
                return;
            }
            
            int mid = (l + r) >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            
            out[u] = cnt++;
            in[u] = cnt++;
            
            add(out[u << 1], out[u], 0);
            add(out[u << 1 | 1], out[u], 0);
            add(in[u], in[u << 1], 0);
            add(in[u], in[u << 1 | 1], 0);
        };

        cnt = n;
        build(1, 1, n);
    }

    void update1(int u, int l, int r, int x, int y, int v, int c){
        if (x <= l && r <= y){
            add(v, in[u], c);
            return;
        }
        int mid = (l + r) >> 1;
        if(x <= mid){
            update1(u << 1, l, mid, x, y, v, c);
        }
        if(mid < y){
            update1(u << 1 | 1, mid + 1, r, x, y, v, c);
        }
    }
    
    void update1(int l, int r, int v, int c){
        update1(1, 1, n, l, r, v, c);
    }

    void update2(int u, int l, int r, int x, int y, int v, int c){
        if (x <= l && r <= y){
            add(out[u], v, c);
            return;
        }
        int mid = (l + r) >> 1;
        if(x <= mid){
            update2(u << 1, l, mid, x, y, v, c);
        }
        if(mid < y){
            update2(u << 1 | 1, mid + 1, r, x, y, v, c);
        }
    }
    
    void update2(int l, int r, int v, int c){
        update2(1, 1, n, l, r, v, c);
    }
};