template <typename T>
struct Fenwick{
    int n;
    vector<T> a, b;
    
    Fenwick(int n = 0){
        init(n);
    }
    
    void init(int len){
        n = len;
        a.assign(n, T{});
        b.assign(n, T{});
    }

    int lowbit(int i){
        return i & -i;
    }
    
    void add(ll x, const T &v) {
        for(ll i = x; i <= n; i += lowbit(i)){
            b[i] += x * v, a[i] += v;
        }
    }

    T query(ll x) {
        ll sum = 0;
        for(ll i = x; i; i -= lowbit(i)){
            sum += (x + 1) * a[i] - b[i];
        }
        return sum;
    }
    
    T range_query(int l, int r) {
        return query(r) - query(l);
    }
};