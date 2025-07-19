template<class Node>
struct Splay{
    const int n, INF = (int)1e9;
    int root, idx;

    vector<Node> tr;

    Splay(int _n) : n(_n), tr(_n) {
        root = idx = 0;
    }

    void pushup(int x){
        tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
    }

    void pushdown(int x){
        if(tr[x].splay){
            swap(tr[x].s[0], tr[x].s[1]);
            tr[tr[x].s[0]].splay ^= 1;
            tr[tr[x].s[1]].splay ^= 1;
            tr[x].splay = 0;
        }
    }

    void rotate(int x){
        int y = tr[x].p, z = tr[y].p, k = tr[y].s[1] == x;
        tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
        tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
        tr[x].s[k ^ 1] = y, tr[y].p = x;

        pushup(y), pushup(x);
    }

    void splay(int x, int k){
        while(tr[x].p != k){
            int y = tr[x].p, z = tr[y].p;
            if(z != k){
                if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)){
                    rotate(x);
                }
                else{
                    rotate(y);
                }
            }
            rotate(x);
        }
        if(!k){
            root = x;
        }
    }

    void insert(int v){
        int u = root, p = 0;
        while(u){
            p = u, u = tr[u].s[v > tr[u].v];
        }

        u = ++idx;
        if(p){
            tr[p].s[v > tr[p].v] = u;
        }
        tr[u].init(v, p);
        splay(u, 0);
    }

    int kth(int k){
        int u = root;
        while(1){
            pushdown(u);
            if(tr[tr[u].s[0]].size >= k){
                u = tr[u].s[0];
            }
            else if(tr[tr[u].s[0]].size + 1 == k){
                return u;
            }
            else{
                k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
            }
        }
        return -1;
    }
};

struct Node{
    int s[2], p, v;
    int size, splay;

    void init(int _v, int _p){
        v = _v;
        p = _p;
        size = 1;
    }
};

//splay(n + 3) -> {0 -> -INF, splay(n + 1), n + 2 -> INF}