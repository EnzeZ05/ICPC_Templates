auto dfs = [&](auto& self, int u, int fa) -> void{
    sz[u] = 1;
    int flag = 1;

    for(int i = h[u];i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa){
            continue;
        }
        self(self, j, u);
        sz[u] += sz[j];
        if(sz[j] > n / 2){ 
            flag = 0;
        }
    }
    if(n - sz[u] > n / 2){ 
        flag = 0;
    }
    if(flag){
        rt = u;
    }
};