struct BCT{
    vector<vector<int>> G, H;
    vector<int> fa, dfn, low, cut;
    stack<int> stk;
    
    int timestamp, tot, n, root;
    BCT(int _n) : n(_n << 1), fa(_n << 1), dfn(_n << 1), low(_n << 1), cut(_n << 1){
        G.resize(_n << 1);
        H.resize(_n << 1);
        tot = _n;
    }

    void add(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void work(int root = 1){
        this->root = root;
        tarjan(root);
    }

    void tarjan(int u){
        dfn[u] = low[u] = ++timestamp;
        stk.push(u);

        int cnt = 0;
        for(auto v : G[u]){
            if(!dfn[v]){
                cnt++;
                tarjan(v);
                low[u] = chmin(low[u], low[v]);
                
                if(dfn[u] == low[v]){
                    if(u != root){ 
                        cut[u] = 1;
                    }
                    ++tot;

                    while(1){
                        int x = stk.top();
                        stk.pop();

                        H[tot].push_back(x);
                        fa[x] = tot;
                        if(x == v){
                            break;
                        }
                    }

                    fa[tot] = u;
                    H[u].push_back(tot);
                }
            }
            else{
                low[u] = chmin(low[u], dfn[v]);
            }
        }

        if(cnt >= 2 && u == root){
            cut[u] = 1;
        }
    }
};