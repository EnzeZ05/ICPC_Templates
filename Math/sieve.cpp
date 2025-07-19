
struct Sieve{
    int n, cnt;
    vector<int> p, p_min, mu;
    Sieve(int _n) : n(_n) {
        p_min.resize(n + 1, 0);
        mu.resize(n + 1, 0);
        init();
    }

    void init(){
        cnt = 0;
        mu[1] = 1;
        for(int i = 2; i <= n; ++i) {
            if(!p_min[i]) {
                mu[i] = -1;
                p.pb(i);
            }

            for(int pr : p) {
                if(i * pr > n) break;
                p_min[i * pr] = pr;  
                if(i % pr == 0) {
                    break;
                }
                mu[i * pr] = -mu[i];
            }
        }
    }
};