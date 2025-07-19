struct Basis{
    static const int bits = 62;

    vector<ll> bs, t;
    int flag, sz;

    Basis() : bs(bits + 1), t(bits + 1), flag(0), sz(0) {}

    void insert(ll x){
        for(int i = bits; i >= 0; i--){
            if(x & (1ll << i)){
                if(!bs[i]){
                    bs[i] = x;
                    sz++;
                    return;
                }
                x ^= bs[i];
            }
        }
        flag = 1;
    }

    int check(ll x){ //查询一个数是否可以被一堆数异或出来
        if(x == 0){
            return 1;
        }
        for(int i = bits; i >= 0; i--){
            if(x & (1ll << i)){
                if(!bs[i]) return 0;
                x ^= bs[i];
            }
        }
        return 1;
    }

    ll get_max(ll res = 0){ //查询异或最大值
        for(int i = bits; i >= 0; i--){
            res = chmax(res, res ^ bs[i]);
        }
        return res;
    }

    ll get_min(){ //查询异或最小值
        if(flag){
            return 0;
        }
        for(int i = 0; i <= bits; i++){
            if(bs[i]) return bs[i];
        }
        return 0;
    }

    ll query(ll k){ //查询异或第k大值
        ll res = 0, cnt = 0;

        k -= flag;
        if(!k){
            return 0;
        }

        for(int i = 0; i <= bits; i++){
            for(int j = i - 1; j >= 0; j--){
                if(bs[i] & (1ll << j)){
                    bs[i] ^= bs[j];
                }
            }
            if(bs[i]) t[cnt++] = bs[i];
        }

        if(k >= (1ll << cnt)){
            return -1;
        }

        for(int i = 0; i < cnt; i++){
            if(k & (1ll << i)){
                res ^= t[i];
            }
        }
        return res;
    }
};