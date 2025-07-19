int h[N], w[N], st[N], e[M], ne[M], idx, n, k, c, pt, dt;
ll d[N], f[N];

void add(int u, int v, int c){
    e[idx] = v, w[idx] = c, ne[idx] = h[u], h[u] = idx++;
}

int get_size(int u, int fa){
    if(st[u]) return 0;
    int sz = 1;
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa) continue;
        sz += get_size(j, u);
    }
    return sz;
}

int get_center(int u, int fa, int sz){
    if(st[u]) return 0;
    int qwq = 1, uwu = 0;
    
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa) continue;
        int owo = get_center(j, u, sz);
        uwu = chmax(owo, uwu);
        qwq += owo;
    }
    
    uwu = chmax(uwu, sz - qwq);
    if(uwu <= sz / 2) c = u;
    return qwq;
}

void get_dist(int u, int fa, int dist){
    if(st[u]) return;
    d[dt++] = dist;
    
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa) continue;
        get_dist(j, u, dist + w[i]);
    }
}

ll calc(int u){
    if(st[u]) return 0;
    int sz = get_size(u, -1);
    get_center(u, -1, sz);
    u = c;

    st[u] = 1;
    
    ll qwq = 0;
    pt = 0;
   
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        get_dist(j, -1, w[i]);
        
        for(int j = 0; j < dt; j++){
            if(d[j] <= k){
                qwq++;
            }
            f[pt++] = d[j];
        }
        sort(d, d + dt);

        for(int l = 0, r = dt - 1; l < r; l++){
            while(d[l] + d[r] > k) r--;
            if(r <= l) break;
            qwq -= (r - l);
        }
        dt = 0;
    }
    
    sort(f, f + pt);
    for(int i = 0, j = pt - 1; i < j; i++){
        while(f[i] + f[j] > k) j--;
        if(j <= i) break;
        qwq += (j - i);
    }

    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        qwq += calc(j);
    }
    return qwq;
}

/*
for(int i = 0; i <= n; i++){
    d[i] = f[i] = st[i] = 0;
    h[i] = -1;
}
idx = c = pt = dt = 0;

cout << calc(0) << endl;
*/