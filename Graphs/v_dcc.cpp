struct V_DCC{
    int n, cur, timestamp, top, dcc_cnt, rt;
 
    vector<int> dfn, low, stk, cut, dccf;
    vector<vector<int>> g, dcc;
 
    V_DCC() {}
    V_DCC(int _n) : n(_n), dfn(_n), low(_n), stk(_n), dccf(_n), cut(_n){
        dcc.assign(n, {});
        g.assign(n, {});
 
        cur = timestamp = top = dcc_cnt = rt = 0;
    }
 
    void add(int u, int v){ 
        g[u].pb(v);
    }
    
    void tarjan(int u) {
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;

        if(u == rt && g[u].size() == 0){
            dccf[u] = dcc_cnt;
            dcc[++dcc_cnt].pb(u);
            return;
        }
     
        int cnt = 0;
        for(auto j : g[u]){
            if(!dfn[j]){
                cnt++;
                tarjan(j);
                low[u] = chmin(low[u], low[j]);
     
                if(dfn[u] <= low[j]){ // < 为割边
                    if(u != rt){ 
                        cut[u] = 1;
                    }
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

        if(cnt >= 2 && u == rt){
            cut[u] = 1;
        }
    }
};

//联通量的边的
struct V_DCC{
    int n, cur, timestamp, top, dcc_cnt, rt;
 
    vector<int> dfn, low, stk, cut, dccf;
    vector<vector<pair<int, int>>> g;
    vector<vector<int>> dcc;
 
    V_DCC() {}
    V_DCC(int _n) : n(_n), dfn(_n), low(_n), stk(_n), dccf(_n), cut(_n){
        dcc.assign(n, {});
        g.assign(n, {});
 
        cur = timestamp = top = dcc_cnt = rt = 0;
    }
 
    void add(int u, int v, int id){  
        g[u].pb({v, id});
    }
    
    void tarjan(int u, int fa) {
        dfn[u] = low[u] = ++timestamp;
     
        int cnt = 0;
        for(auto pair : g[u]){
            int v = pair.first, id = pair.second;
            if(v == fa){
                continue;
            }
            if(!dfn[v]){
                stk[++top] = id;
                tarjan(v, u);
                low[u] = chmin(low[u], low[v]);
     
                if(dfn[u] <= low[v]){  
                    ++dcc_cnt;
                    while(stk[top] != id){
                        dcc[dcc_cnt].pb(stk[top--]);
                    }
                    dcc[dcc_cnt].push_back(stk[top--]);
                }
            }
            else if(dfn[v] < dfn[u]){
                stk[++top] = id;
                low[u] = chmin(low[u], dfn[v]);
            }
        }
    }
};