struct XORTrie{
    vector<array<int, 2>> f;
    vector<int> cnt;
    
    int n, idx, bits;

    XORTrie(int _n, int _bits){
        n = _n;
        idx = 0;
        bits = _bits;

        f.resize(n + 1, array<int, 2>());
        cnt.resize(n + 1);
    }

    void insert(int a){
        int p = 0;
        for(int i = bits; i >= 0; i--){
            int u = (a >> i & 1);
            if(!f[p][u]){
                f[p][u] = ++idx;
            }
            p = f[p][u];
            ++cnt[p];
        }
    }

    void remove(int a) {
        int p = 0;
        for(int i = bits; i >= 0; i--){
            int u = (a >> i & 1);
            p = f[p][u];
            --cnt[p];
        }
    }

    int search(int a){
        int p = 0, t = 0;
        for(int i = bits; i >= 0; i--){
            int u = !(a >> i & 1);
            if(f[p][u] && cnt[f[p][u]]){
                p = f[p][u];
                t += (1 << i);
            }
            else if(f[p][!u] && cnt[f[p][!u]]){
                p = f[p][!u];
            }
        }
        return t;
    }
};

