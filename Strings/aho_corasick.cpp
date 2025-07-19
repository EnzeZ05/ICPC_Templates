struct AhoCorasick{
    static constexpr int s = 26;
    
    struct P{
        int len, k;
        array<int, s> f;
        P() : len{0}, k{0}, f{} {}
    };
    
    vector<int> cnt;
    vector<P> tr;

    AhoCorasick(int n) : cnt(n) {
        init();
    }
    
    void init() {
        tr.assign(2, P());
        tr[0].f.fill(1);
        tr[0].len = -1;
    }
    
    int new_p() {
        tr.emplace_back();
        return tr.size() - 1;
    }
    
    int insert(const string &s) {
        int p = 1;
        for (auto ch : s) {
            int idx = ch - 'a';
            if (tr[p].f[idx] == 0) {
                tr[p].f[idx] = new_p();
                tr[tr[p].f[idx]].len = tr[p].len + 1;
            }
            p = tr[p].f[idx];
        }
        cnt[p]++;
        return p;
    }
    
    void build() {
        queue<int> q;
        q.push(1);
        
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            
            for(int i = 0; i < s; i++){
                if(tr[cur].f[i] == 0){
                    tr[cur].f[i] = tr[tr[cur].k].f[i];
                } 
                else{
                    tr[tr[cur].f[i]].k = tr[tr[cur].k].f[i];
                    q.push(tr[cur].f[i]);
                }
            }
        }
    }
    
    int next(int p, int ch) { 
        return tr[p].f[ch];
    }
    
    int get_k(int p) { //找到p的fail指针
        return tr[p].k;
    }
    
    int get_len(int p) {
        return tr[p].len;
    }
    
    int get_sz() {
        return tr.size();
    }
}; //初始指针下标从1开始

// void solve(){
//     int n;
//     cin >> n;

//     AhoCorasick ah(N);
//     for(int i = 0; i < n; i++){
//         string s;
//         cin >> s;
//         ah.insert(s);
//     }

//     string t;
//     cin >> t;

//     ah.build();

//     ll qwq = 0;
//     for(int i = 0, j = 1; t[i]; i++){
//         int c = t[i] - 'a';
//         j = ah.next(j, c); //找到链
//         int p = j;
//         while(p){
//             qwq += ah.cnt[p];
//             ah.cnt[p] = 0;
//             p = ah.get_k(p); //开跳！
//         }
//     }
//     cout << qwq << endl;
// }
