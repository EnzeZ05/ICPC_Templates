struct SCC{
    vector<int> dfn, low, stk, id, visited;
    vector<vector<int>> adj;
    int timestamp, top, cnt, n;

    SCC(int _n) : dfn(_n), low(_n), stk(_n), id(_n), visited(_n), adj(_n){
        timestamp = top = cnt = 0;
        n = _n;
    }

    void add(int u, int v){
        adj[u].push_back(v); 
    }

    void tarjan(int u){
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;
        visited[u] = true;

        for(int j : adj[u]){
            if(dfn[j] == 0){
                tarjan(j);
                low[u] = chmin(low[u], low[j]);
            } 
            else if (visited[j]){
                low[u] = chmin(low[u], dfn[j]);
            }
        }

        if(dfn[u] == low[u]){ 
            int y;
            ++cnt;
            do{
                y = stk[top--];
                visited[y] = false;
                id[y] = cnt; 
            }while(y != u);
        }
    }
};