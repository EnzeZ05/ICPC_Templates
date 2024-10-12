struct Cut_Point{
    int n, cur, timestamp, top, dcc_cnt, cntc;

    vector<int> dfn, low, stk, cut, dccf;
    vector<vector<int>> g, dcc;
    map<int, int> vis; 

    Cut_Point() {}
    Cut_Point(int _n) : n(_n), dfn(_n), low(_n), stk(_n), dccf(_n), cut(_n){
        dcc.assign(n, {});
        g.assign(n, {});

        cur = timestamp = top = dcc_cnt = cntc = 0;
    }

    void add(int u, int v){ //scc / bcc
        g[u].pb(v);
    }
    
    void tarjan(int u) {
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;
     
        if(u == 1 && g[u].size() == 0){
            dcc_cnt++;
            dcc[dcc_cnt].push_back(u);
            return;
        }
     
        int cnt = 0;
        for(auto j : g[u]){
            if(!dfn[j]){
                tarjan(j);
                low[u] = chmin(low[u], low[j]);
     
                if(dfn[u] <= low[j]){
                    if(u != 1 || cnt > 1) cut[u] = true;
                    ++dcc_cnt;
     
                    int y;
                    do{ 
                        y = stk[top--];
                        dccf[y] = dcc_cnt;
                        dcc[dcc_cnt].push_back(y);
                    }while(y != j);
     
                    dcc[dcc_cnt].push_back(u);
                }
            }
            else{
                low[u] = chmin(low[u], dfn[j]);
            }
        }
    }
};