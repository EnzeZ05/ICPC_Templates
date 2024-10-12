struct P{
    int id, l, r;
};

struct Mo{
    map<int, int> mp;
    vector<int> w;
    vector<P> a;
    int len;
    P p;

    Mo(int n){
        w = vector<int>(n);
        a = vector<P>(n);

        len = (int)sqrt(n);
    }

    Mo(int n, vector<P> vec){
        w = vector<int>(n);
        a = vec;

        len = (int)sqrt(n);
    }

    void assign(int i, int u){
        w[i] = u;
    }

    int get(int i){
        return i / len;
    }

    bool cmp(const P& a, const P& b){
        int al = get(a.l), ar = get(a.r);
        int bl = get(b.l), br = get(b.r);

        if(al != bl) return a.l < b.l;
        return a.r < b.r;
    }

    void add(int i, int& qwq){
        if(!mp[i]){
            qwq++;
        }
        mp[i]++;
    }

    void del(int i, int& qwq){
        mp[i]--;
        if(!mp[i]){
            qwq--;
        }
    }

    void calc(){
        sort(a.begin(), a.end(), cmp);

        for(int k = 0, i = 0, j = 1, qwq = 0; k < a.size(); k++){
            int id = a[k].id, l = a[k].l, r = a[k].r;
            while(i < r) add(w[++i], qwq);
            while(i > r) del(w[i--], qwq);
            while(j < l) del(w[j++], qwq);
            while(j > l) add(w[--j], qwq);
            //op
        }
    }
 
}; 

//普通莫队 块 sqrt(n)
//修改莫队 多结构体 块 sqrt(n ^ (2/3));
//回滚莫队 修改难 块 sqrt(n)
