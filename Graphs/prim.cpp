int n;
int v[N];
ll d[N], a[N][N];

void Prim(){
    fill(vis, vis + n + 1, 0);
    fill(dis, dis + n + 1, INF);
    d[1] = 0;

    for(int i = 1; i < n; ++i){
        int x = 0;
        for(int j = 1; j <= n; ++j){
            if(!v[j] && (x == 0 || d[j] < d[x])){
                x = j;
            }
        }
        
        v[x] = 1;
        for(int y = 1; y <= n; ++y){
            if(!v[y]){
                d[y] = chmin(d[y], a[x][y]);
            }
        }
    }
}
