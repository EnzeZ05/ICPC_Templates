template<class Node>
struct Treap{
    const int n, INF = (int)1e9;
    int root, idx;

    vector<Node> tr;

    Treap(int _n) : n(_n), tr(_n) {
        root = idx = 0;
    }

    void push_up(int u){
        tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;
    }

    void right_splay(int& u){
        int v = tr[u].l;
        tr[u].l = tr[v].r, tr[v].r = u, u = v;
        push_up(tr[u].r), push_up(u);
    }

    void left_splay(int &u){
        int v = tr[u].r;
        tr[u].r = tr[v].l, tr[v].l = u, u = v;
        push_up(tr[u].l), push_up(u);
    }

    int add(ll key){
        tr[++idx].key = key;
        tr[idx].val = rand();
        tr[idx].cnt = tr[idx].size = 1;
        return idx;
    }

    void build(){
        add(-INF);
        add(INF);

        root = 1;
        tr[root].r = root + 1;
        push_up(root);

        if(tr[1].val < tr[2].val){
            left_splay(root);
        }
    }

    void insert(int &u, int key){
        if(!u){
            u = add(key);
        }
        else{
            if(tr[u].key == key){
                tr[u].cnt++;
            }
            else{
                if(tr[u].key > key){
                    insert(tr[u].l, key);
                    if(tr[tr[u].l].val > tr[u].val){
                        right_splay(u);
                    }
                }
                else{
                    insert(tr[u].r, key);
                    if(tr[tr[u].r].val > tr[u].val){
                        left_splay(u);
                    }
                }
            }
        }
        push_up(u);
    }

    void insert(int x){
        insert(root, x);
    }

    void remove(int &u, int key){
        if(!u) return;
        if(tr[u].key == key){
            if(tr[u].cnt > 1){
                tr[u].cnt--;
            }
            else{
                if(tr[u].l || tr[u].r){
                    if(!tr[u].r || tr[tr[u].l].val > tr[tr[u].r].val){
                        right_splay(u);
                        remove(tr[u].r, key);
                    }
                    else{
                        left_splay(u);
                        remove(tr[u].l, key);
                    }
                }
                else{
                    u = 0;
                }
            }
        }
        else{
            if(tr[u].key > key){
                remove(tr[u].l, key);
            }
            else{
                remove(tr[u].r, key);
            }
        }

        push_up(u);
    }

    void remove(int x){
        remove(root, x);
    }

    int rank(int& u, int key){
        if(!u) return 0;
        if(tr[u].key == key){
            return tr[tr[u].l].size + 1; 
        }
        if(tr[u].key > key){
            return rank(tr[u].l, key);
        }
        return tr[tr[u].l].size + tr[u].cnt + rank(tr[u].r, key);
    }

    int rank(int x){
        insert(x);
        int p = rank(root, x) - 1; //烧饼
        remove(x);
        return p;
    }

    int kth(int& u, int k){
        if(!u) return INF;
        if(tr[tr[u].l].size >= k){
            return kth(tr[u].l, k);
        }
        else if(tr[tr[u].l].size + tr[u].cnt >= k){
            return tr[u].key;
        }
        return kth(tr[u].r, k - tr[tr[u].l].size - tr[u].cnt);
    }

    int kth(int x){
        return kth(root, x + 1); //烧饼
    }

    int prev(int& u, int key){
        if(!u) return -INF;
        if(tr[u].key >= key){
            return prev(tr[u].l, key);
        }
        return chmax(tr[u].key, prev(tr[u].r, key));
    }

    int prev(int x){
        return prev(root, x);
    }

    int next(int& u, int key){
        if(!u) return INF;
        if(tr[u].key <= key){
            return next(tr[u].r, key);
        }
        return chmin(tr[u].key, next(tr[u].l, key));
    }

    int next(int x){
        return next(root, x);
    }
};

struct Node{
    int l, r;
    int key, val, cnt, size;
};