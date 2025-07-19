bool hungarian(int x){ //图
    for(int i = h[x]; i != -1; i = ne[i]){
        int j = e[i];
        if (!st[j]){
            st[j] = 1;
            if(match[j] == 0 || hungarian(match[j])){
                match[j] = x;
                return 1;
            }
        }
    }
    return 0;
}

bool hungarian(int x, int y){ //格
    for(int i = 0; i < 4; i++){
        int dx = x + dir_x[i], dy = y + dir_y[i];
        if(dx < 1 || dy < 1 || dx > n || dy > m)
            continue;
        if(st[dx][dy] || g[dx][dy])
            continue;
        
        st[dx][dy] = 1; 
        Node t = match[dx][dy];
        if(t == null || hungarian(t.x, t.y)){ 
            match[dx][dy] = {x, y};
            return 1;
        } 
    }
    return 0;
}

int res = 0;
for(int i = 1; i <= n1; i ++ ){
    fill(st, 0);
    if(hungarian(i)){
        //
    }
}