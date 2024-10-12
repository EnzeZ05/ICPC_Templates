struct CostFlow {
    using V = bool;
    using E = int;

    E id, s, t, n, m;
    T INF;

    vector<E> pre, h, ne, e;
    vector<T> d, f, w, incf;
    vector<V> st;

    V rev;

    CostFlow(E n, E m, E s, E t, T INF): n(n), m(m), INF(INF), s(s), t(t){
        h.assign(n, -1), pre.resize(n), incf.resize(n), st.resize(n), d.resize(n);
        e.resize(m << 1), ne.resize(m << 1), f.resize(m << 1), w.resize(m << 1);
        rev = id = 0;
    }

    T EK(){
        T cost = 0;
        while(spfa()){
            T tmp = incf[t];
            cost += d[t] * tmp;
            for(E i = t; i != s; i = e[pre[i] ^ 1]){
                f[pre[i]] -= tmp;
                f[pre[i] ^ 1] += tmp;
            }
        }
        return rev ? -cost : cost;
    }

    void reverse(){
        for(E i = 0; i < id; i += 2){
            f[i] += f[i ^ 1];
            f[i ^ 1] = 0;
            w[i] = -w[i];
            w[i ^ 1] = -w[i ^ 1];
        }
        rev = 1;
    }

    V spfa(){
        fill(d.begin(), d.end(), INF);
        fill(incf.begin(), incf.end(), 0);
        queue<E> q;

        q.push(s); d[s] = 0; incf[s] = INF;
        st.assign(n, 0);
        st[s] = 1;
        
        while(!q.empty()){
            E u = q.front(); q.pop();
            st[u] = 0;
            for(E i = h[u]; i != -1; i = ne[i]){
                E v = e[i];
                if(f[i] > 0 && d[v] > d[u] + w[i]){
                    d[v] = d[u] + w[i];
                    pre[v] = i;
                    incf[v] = chmin(incf[u], f[i]);
                    if(!st[v]){
                        q.push(v);
                        st[v] = 1;
                    }
                }
            }
        }
        return incf[t] > 0;
    }

    void add(E u, E v, T cap, T cost){
        e[id] = v; f[id] = cap; w[id] = cost; ne[id] = h[u]; h[u] = id++;
        e[id] = u; f[id] = 0; w[id] = -cost; ne[id] = h[v]; h[v] = id++;
    }
};