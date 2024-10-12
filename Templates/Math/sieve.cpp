struct Sieve{
    int n, cnt;
    vector<int> p, st;
    Sieve(int _n) : n(_n) {
        st.resize(n + 1, 0);
    }

    void init(){
        cnt = 0;
        for(int i = 2; i <= n; ++i) {
            if(!st[i]) {
                p.pb(i);
            }

            for(int e : p) {
                if(i * e > n) break;
                st[i * e] = true;
                if(i % e == 0) {
                    break;
                }
            }
        }
    }
};