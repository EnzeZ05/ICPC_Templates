template<typename T>
struct MaxFlow {
    using V = bool;
    using E = int;

    vector<E> h, e, ne, cur;
    vector<T> f, d;

    E id, s, t, n, m;
    T INF;

    MaxFlow(E n, E m, E s, E t, T INF): n(n), m(m), s(s), t(t), INF(INF){
        e.resize(m << 1), ne.resize(m << 1), f.resize(m << 1);
        h.assign(n, -1), cur.resize(n), d.resize(n);
        id = 0;
    }

    V bfs(){
        queue<E> q;
        q.push(s);
        fill(d.begin(), d.end(), -1);
        d[s] = 0;
        cur[s] = h[s];

        while(!q.empty()){
            E u = q.front(); 
            q.pop();

            for(E i = h[u]; i != -1; i = ne[i]){
                E v = e[i];
                if(d[v] == -1 && f[i] > 0){
                    d[v] = d[u] + 1;
                    cur[v] = h[v];
                    if(v == t) return 1;
                    q.push(v);
                }
            }
        }
        return 0;
    }

    T find(E u, T flow_limit){
        if(u == t) return flow_limit;
        T flow = 0;
        for(E i = cur[u]; i != -1 && flow < flow_limit; i = ne[i]){
            E v = e[i];

            if(d[v] == d[u] + 1 && f[i] > 0){
                T tmp = find(v, chmin(flow_limit - flow, f[i]));
                if(tmp > 0){
                    f[i] -= tmp;
                    f[i ^ 1] += tmp;
                    flow += tmp;
                }  
                else{
                    d[v] = -1;
                }
            }
        }
        return flow; 
    }

    T dinic(){
        T maxflow = 0;
        while(bfs()){
            T flow;
            while((flow = find(s, INF)) > 0){
                maxflow += flow;
            }
        }
        return maxflow;
    }

    void add(E u, E v, T cap){
        e[id] = v; f[id] = cap; ne[id] = h[u]; h[u] = id++;
        e[id] = u; f[id] = 0; ne[id] = h[v]; h[v] = id++;
    }
};

