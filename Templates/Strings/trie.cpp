
struct Trie{
    vector<vector<int>> f;
    vector<int> cnt;
    
    int n, idx;

    Trie(int _n){
        n = _n;
        idx = 0;

        f.resize(n + 1, vector<int>(26));
        cnt.resize(n + 1);
    }

    void insert(string s){
        int p = 0;
        for(int i = 0; s[i]; i++){
            int u = s[i] - 'a';
            if(!f[p][u]) f[p][u] = ++idx;
            p = f[p][u];
        }
        cnt[p]++;
    }

    int search(string s){
        int p = 0;
        for(int i = 0; s[i]; i++){
            int u = s[i] - 'a';
            if(!f[p][u]) return 0;
            p = f[p][u];
        }
        return cnt[p];
    }
};