const int N = (int)2e5 + 1, M = N * 2;
int h[N], w[N], st[N], e[M], ne[M], idx, c;


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