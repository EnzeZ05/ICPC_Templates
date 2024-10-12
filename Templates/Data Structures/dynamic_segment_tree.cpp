template<class Operation>
struct SegTree{
    const ll n, len;
    ll pos, root;
 
    struct Node {
        ll l, r;
        Operation op;
    };
 
    vector<Node> f;
 
    SegTree(ll n, ll len) : n(n), len(len), f(4 << __lg(n)), pos(0), root(0){}
 
    void pushup(ll u) {
        f[u].op = f[f[u].l].op + f[f[u].r].op;
    }
 
    void update(ll &u, ll l, ll r, ll x, const Operation &v){
        if(!u){
            u = ++pos;
            f[u].op = {};
            f[u].l = f[u].r = 0;
        }
        if(l == r){
            f[u].op = v; //也许会变
            return;
        }
        ll m = (l + r) >> 1;
        if(x <= m) {
            update(f[u].l, l, m, x, v);
        }
        else{
            update(f[u].r, m + 1, r, x, v);
        }

        pushup(u);
    }
 
    void update(ll &root, ll u, const Operation &v){
        update(root, 1, len, u, v);
    }

    void modify(ll u, ll v){
        //值合并操作
    }

    ll merge(ll u, ll v, ll l, ll r){
        if(!u){
            return v;
        }
        if(!v){
            return u;
        }
        if(l == r){
            modify(u, v);
            return u;
        }

        ll m = (l + r) >> 1;
        f[u].l = merge(f[u].l, f[v].l, l, m);
        f[u].r = merge(f[u].r, f[v].r, m + 1, r);
        pushup(u);
        return u;
    }

    Operation query(ll u, ll l, ll r, ll x, ll y){
        if(!u){
            return {};
        }
        if(x <= l && r <= y) {
            return f[u].op;
        }
 
        ll m = (l + r) >> 1;
        Operation cur;
        if(x <= m) {
            cur = query(f[u].l, l, m, x, y);
        }
        if(y > m) {
            cur = cur + query(f[u].r, m + 1, r, x, y);
        }
        return cur;
    }
 
    Operation query(ll &root, ll l, ll r){
        return query(root, 1, len, l, r);
    }

    // Operation kth(ll u, ll l, ll r, ll t){
    //     if(!u){
    //         return {};
    //     }
    //     if(l == r){
    //         return f[u].op;
    //     }
        
    //     int m = l + r >> 1;

    //     if(f[f[u].l].op.cnt >= t){
    //         return kth(f[u].l, l, m, t);
    //     }
    //     else{
    //         return kth(f[u].r, m + 1, r, t - f[f[u].l].op.cnt);
    //     }
    // }

    // Operation kth(ll &root, ll t){
    //     return kth(root, 1, len, t);
    // }
};

//预处理根

struct Operation{ 
    Operation(){
   
    }
};
 
Operation operator+(Operation a, Operation b){

}