template<class Operation, class Mark>
struct LCT{
    struct Node{
        int ch[2];  
        int fa;       
        bool rev;     
        Operation val, info; 
        Mark lazy;   
 
        Node() : fa(0), rev(false), val(Operation()), info(Operation()), lazy(Mark()){
            ch[0] = ch[1] = 0;
        }
    };
 
    const int n;
    vector<Node> tr; 
 
    LCT(int n) : n(n), tr(n + 1) {}
 
    inline bool isRoot(int x){
        int f = tr[x].fa;
        return (f == 0 || tr[f].ch[0] != x && tr[f].ch[1] != x);
    }
 
    inline int dir(int x){
        int f = tr[x].fa;
        return tr[f].ch[1] == x;
    }
 
    void pushup(int x) {
        tr[x].info = tr[x].val;
        if(tr[x].ch[0]){
            tr[x].info = tr[tr[x].ch[0]].info + tr[x].info;
        }
        if(tr[x].ch[1]){
            tr[x].info = tr[x].info + tr[tr[x].ch[1]].info;
        }
    }
 
    void apply(int x, const Mark &mk) {
        tr[x].val.modify(mk);
        tr[x].info.modify(mk);
        tr[x].lazy.modify(mk);
    }
 
    void pushdown(int x){
        if(tr[x].rev){
            int l = tr[x].ch[0], r = tr[x].ch[1];
            if(l){
                tr[l].rev ^= 1;
                swap(tr[l].ch[0], tr[l].ch[1]);
            }
            if(r){
                tr[r].rev ^= 1;
                swap(tr[r].ch[0], tr[r].ch[1]);
            }
            tr[x].rev = 0;
        }
        if(tr[x].lazy.add){
            int l = tr[x].ch[0], r = tr[x].ch[1];
            if(l){
                apply(l, tr[x].lazy);
            }
            if(r){
                apply(r, tr[x].lazy);
            }
            tr[x].lazy = Mark();
        }
    }
 
    void rotate(int x) {
        int y = tr[x].fa, z = tr[y].fa;
        int d = dir(x);
        if (!isRoot(y)){
            tr[z].ch[tr[z].ch[1] == y] = x;
        }
 
        tr[x].fa = z;
        tr[y].ch[d] = tr[x].ch[d ^ 1];
 
        if(tr[x].ch[d ^ 1]){
            tr[tr[x].ch[d ^ 1]].fa = y;
        }
 
        tr[x].ch[d ^ 1] = y;
        tr[y].fa = x;
        pushup(y);
        pushup(x);
    }
 
    void splay(int x) {
        vector<int> anc;
        int y = x;
        anc.push_back(y);
 
        while(!isRoot(y)){
            anc.push_back(tr[y].fa);
            y = tr[y].fa;
        }
 
        for(int i = anc.size() - 1; i >= 0; i--){
            pushdown(anc[i]);
        }
 
        while(!isRoot(x)){
            int y = tr[x].fa, z = tr[y].fa;
            if(!isRoot(y)){
                if((tr[z].ch[0] == y) ^ (tr[y].ch[0] == x)){
                    rotate(x);
                }
                else{
                    rotate(y);
                }
            }
            rotate(x);
        }
    }
 
    void access(int x){
        int z = x;
        for(int y = 0; x; x = tr[x].fa){
            splay(x);
            tr[x].ch[1] = y;
            pushup(x);
            y = x;
        }
        splay(z);
    }
 
    void make_root(int x){
        access(x);
        splay(x);
        tr[x].rev ^= 1;
        swap(tr[x].ch[0], tr[x].ch[1]);
    }
 
    int find_root(int x) {
        access(x);
        while(tr[x].ch[0]){
            pushdown(x);
            x = tr[x].ch[0];
        }
        splay(x);
        return x;
    }

    void strong_link(int x, int y){
        make_root(x);
        access(y);
    }
 
    void link(int x, int y){
        make_root(x);
        if(find_root(y) != x){
            tr[x].fa = y;
        }
    }
 
    void cut(int x, int y){
        make_root(x);
        if(find_root(y) == x && tr[y].fa == x && !tr[y].ch[0]){
            tr[x].ch[1] = tr[y].fa = 0;
            pushup(x);
        }
    }
 
    void update(int x, const Operation &v){
        splay(x);
        tr[x].val = v;
        pushup(x);
    }
 
    void path_update(int x, int y, const Mark &v){
        make_root(x);
        access(y);
        apply(y, v);
    }

    Operation query(int x, int y){
        strong_link(x, y);
        return tr[y].info;
    }
};

struct Mark{
    int add = 0;
    Mark(int p = 0){
        
    }

    void modify(const Mark &v){
   
    }
};
 
struct Operation{
   
    Operation(int p = 0){
     
    }

    void modify(const Mark &v){
    
    }
};
 
Operation operator+(const Operation &a, const Operation &b){
 
}
