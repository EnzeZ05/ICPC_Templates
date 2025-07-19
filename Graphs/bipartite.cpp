bool dfs(int u, int c, int v){
    color[u] = c;
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(w[i] <= v) continue;
        if(color[j]){  
            if(color[j] == c){ 
                return 0;
            }
        }
        else if(!dfs(j, 3 - c, v))  //  3 - 1 = 2   3 - 2 = 1
            return 0;
    }
    return 1;
}

struct Bipartite { //Ethan-ZYF
    vector<vector<int>> g;
    vector<int> color;

    Bipartite(int n) : g(n), color(n, -1) {}

    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool dfs(int u, int c) {
        color[u] = c;
        for(auto v : g[u]){
            if(color[v] == -1){
                if(!dfs(v, c ^ 1)){
                    return false;
                }
            } 
            else if (color[v] == color[u]){
                return false;
            }
        }
        return true;
    }

    bool work() {
        for (int i = 0; i < g.size(); i++){
            if(color[i] == -1){
                if(!dfs(i, 0)){
                    return false;
                }
            }
        }
        return true;
    }

    vector<int> get_color(){
        return color;
    }
};