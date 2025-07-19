struct Polynomial{
    static const int mod = 998244353;
    static const int g = 3, gi = (mod + 1) / g;

    ll qpow(ll x, ll k){
        ll res = 1;
        while(k > 0){
            if(k & 1){
                res = res * x % mod;
            }
            x = x * x % mod;
            k >>= 1;
        }
        return res;
    }

    vector<int> rev;
    int tot, len;

    void init(int n){
        tot = len = 1;
        while(len <= n * 4){
            len <<= 1;
        }
        while((1 << tot) < len){
            ++tot;
        }

        rev.resize(len);
        for(int i = 0; i < len; i++){
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (tot - 1));
        }
    }

    vector<ll> ntt_conv(const vector<ll>& a, const vector<ll>& b){
        vector<ll> c(tot);
        for (int i = 0; i < tot; i++){
            c[i] = a[i] * b[i] % mod;
        }
        return c;
    }

    void ntt_(vector<ll>& a, int inv){
        for(int i = 0; i < tot; i++){
            if(i < rev[i]){
                swap(a[i], a[rev[i]]);
            }
        }
        for(int mid = 1; mid < tot; mid <<= 1){
            ll tmp = qpow((inv ? g : gi), (mod - 1) / (mid * 2));

            for(int i = 0; i < tot; i += mid * 2) {
                ll w = 1;
                for(int j = 0; j < mid; j++, w = w * tmp % mod){
                    ll x = a[i + j], y = w * a[i + j + mid] % mod;
                    a[i + j] = (x + y) % mod;
                    a[i + j + mid] = (x - y + mod) % mod;
                }
            }
        }
    }
};