int n, m;
int w[N];
vector<int> h[N];
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];

void add(int a, int b) {
    h[a].pb(b);
    h[b].pb(a); // Since it's an undirected tree
}

void dfs1(int u, int father, int depth) {
    dep[u] = depth;
    fa[u] = father;
    sz[u] = 1;
    for (auto v : h[u]) {
        if (v == father) continue;
        dfs1(v, u, depth + 1);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    id[u] = ++cnt;
    nw[cnt] = w[u];
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (auto v : h[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

struct Operation {
    ll sum;
    ll add;
    int len;

    Operation() : sum(0), add(0), len(0) {}

    Operation(ll s, ll a, int l) : sum(s), add(a), len(l) {}
};

Operation operator+(const Operation& a, const Operation& b) {
    return Operation(a.sum + b.sum, 0, a.len + b.len);
}

template<class Operation>
struct SegTree {
    ll n, len;
    ll pos, root;

    struct Node {
        ll l, r;
        ll lc, rc;
        Operation op;

        Node() : l(0), r(0), lc(0), rc(0), op() {}
    };

    vector<Node> f;

    SegTree() : n(0), len(0), pos(1), root(1) {}

    void init(ll _n, ll _len) {
        n = _n;
        len = _len;
        pos = 1;
        root = 1;
        f.assign(4 * len + 5, Node());
        build(root, 1, len);
    }

    void pushup(ll u) {
        f[u].op = f[f[u].lc].op + f[f[u].rc].op;
    }

    void pushdown(ll u) {
        if (f[u].op.add) {
            ll add = f[u].op.add;
            if (f[u].lc) {
                f[f[u].lc].op.sum += add * f[f[u].lc].op.len;
                f[f[u].lc].op.add += add;
            }
            if (f[u].rc) {
                f[f[u].rc].op.sum += add * f[f[u].rc].op.len;
                f[f[u].rc].op.add += add;
            }
            f[u].op.add = 0;
        }
    }

    void build(ll u, ll l, ll r) {
        f[u].l = l;
        f[u].r = r;
        f[u].op.len = r - l + 1;
        if (l == r) {
            f[u].op.sum = nw[l];
            return;
        }
        ll m = (l + r) >> 1;
        f[u].lc = ++pos;
        f[u].rc = ++pos;
        build(f[u].lc, l, m);
        build(f[u].rc, m + 1, r);
        pushup(u);
    }

    void update(ll u, ll l, ll r, ll x, ll y, ll val) {
        if (x <= l && r <= y) {
            f[u].op.sum += val * f[u].op.len;
            f[u].op.add += val;
            return;
        }
        pushdown(u);
        ll m = (l + r) >> 1;
        if (x <= m) update(f[u].lc, l, m, x, y, val);
        if (y > m) update(f[u].rc, m + 1, r, x, y, val);
        pushup(u);
    }

    ll query(ll u, ll l, ll r, ll x, ll y) {
        if (x <= l && r <= y) {
            return f[u].op.sum;
        }
        pushdown(u);
        ll m = (l + r) >> 1;
        ll res = 0;
        if (x <= m) res += query(f[u].lc, l, m, x, y);
        if (y > m) res += query(f[u].rc, m + 1, r, x, y);
        return res;
    }

    void update(ll x, ll y, ll val) {
        update(root, 1, len, x, y, val);
    }

    ll query(ll x, ll y) {
        return query(root, 1, len, x, y);
    }
};

SegTree<Operation> seg;

void update_path(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        seg.update(id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.update(id[u], id[v], k);
}

ll query_path(int u, int v) {
    ll res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += seg.query(id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res += seg.query(id[u], id[v]);
    return res;
}

void update_tree(int u, int k) {
    seg.update(id[u], id[u] + sz[u] - 1, k);
}

ll query_tree(int u) {
    return seg.query(id[u], id[u] + sz[u] - 1);
}

/*
    add(a, b); build graph

    dfs1(1, 0, 1);
    cnt = 0;
    dfs2(1, 1);

    seg.init(cnt, cnt);
*/