struct Block{
    vector<ll> sum, add, w;
    ll len;

    Block(int n){ 
        sum = vector<ll>(n);
        add = vector<ll>(n);
        w = vector<ll>(n);
        len = (ll)sqrt(n);
    }

    int get(int i){
        return i / len;
    }

    void assign(int id, ll u){
        sum[get(id)] += u;
        w[id] = u;
    }

    void modify(int l, int r, int d){
        if(get(l) == get(r)){
            for(int i = l; i <= r; i ++ ){
                sum[get(i)] += d;
                w[i] += d;
            }
        }
        else{
            int i = l, j = r;
            while(get(i) == get(l)){ 
                sum[get(i)] += d;  
                w[i++] += d; 
            }
            while(get(j) == get(r)){ 
                sum[get(j)] += d;
                w[j--] += d; 
            }
            for(int k = get(i); k <= get(j); k++){
                sum[k] += len * d;
                add[k] += d;
            }
        }
    }

    ll query(int l, int r){
        ll res = 0;
        if(get(l) == get(r)){
            for(int i = l; i <= r; i++){
                res += w[i] + add[get(i)];
            }
        }
        else{
            int i = l, j = r;
            while(get(i) == get(l)){ 
                res += w[i] + add[get(i++)]; 
            }
            while(get(j) == get(r)){ 
                res += w[j] + add[get(j--)]; 
            }
            for(int k = get(i); k <= get(j); k++){
                res += sum[k];
            }
        }
        return res;
    }
};