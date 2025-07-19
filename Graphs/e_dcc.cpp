
struct E_DCC{
    int n, idx, cur, cnt, timestamp, top, dcc_cnt;

    vector<int> dfn, low, stk, bridge, dccf, id;
    vector<vector<pair<int, int>>> g;
    vector<vector<int>> dcc;
    E_DCC() {}
    E_DCC(int _n, int _m) : n(_n), dfn(_n), low(_n), stk(_n), dccf(_n), bridge(_m << 1){
        dcc.assign(n, {});
        g.assign(n, {});

        cur = timestamp = top = dcc_cnt = idx = 0;
    }

    void add(int u, int v){
        g[u].pb({v, idx++});
    }
    
    void tarjan(int u, int from){ 
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;
        
        for(auto p : g[u]){
            int j = p.first, i = p.second;
            if(dfn[j] == 0){
                tarjan(j, i);
                low[u] = chmin(low[u], low[j]);
                if(dfn[u] < low[j]){
                    bridge[i] = bridge[i ^ 1] = 1;  
                }
            }
            else if(i != (from ^ 1)){
                low[u] = chmin(low[u], dfn[j]);
            }
        }

        if(dfn[u] == low[u]){
            ++dcc_cnt;
            int y;
            do{
                y = stk[top--];
                dccf[y] = dcc_cnt;
                dcc[dcc_cnt].pb(y);
            } while(y != u);
        }
    }
};