struct Line{
    ll m, b;  
    Line(ll _m, ll _b) : m(_m), b(_b) {}
    
    ll eval(ll x) const { 
        return m * x + b; 
    }
};
 
struct LCTree{
    ll L, R;      
    Line* line = nullptr; 
    LCTree *lch = nullptr, *rch = nullptr;
 
    LCTree(ll _L, ll _R) : L(_L), R(_R) {}
 
    void add(Line* nl, ll l, ll r){
        if(!line){
            line = nl;
            return;
        }
        
        if(l == r){
            if(nl->eval(l) < line->eval(l)){
                swap(nl, line);
            }
            return;
        }
        
        ll mid = (l + r) >> 1;
        bool mBetter = (nl->eval(mid) < line->eval(mid));
        if(mBetter){
            swap(nl, line);
        }
        if(nl->eval(l) < line->eval(l)){
            if (!lch) {
                lch = new LCTree(l, mid);
            }
            lch->add(nl, l, mid);
        }
        else { 
            if(!rch){
                rch = new LCTree(mid + 1, r);
            }
            rch->add(nl, mid + 1, r);
        }
    }
 
    void add(ll m, ll b){
        Line* nl = new Line(m, b);
        add(nl, L, R);
    }
 
    ll query(ll x, ll l, ll r){
        ll ret = (line ? line->eval(x) : INF);
        if(l == r){
            return ret;
        }
        ll mid = (l + r) >> 1;
        if(x <= mid){
            if(lch){
                ret = chmin(ret, lch->query(x, l, mid));
            }
        }
        else{
            if(rch){
                ret = chmin(ret, rch->query(x, mid + 1, r));
            }
        }
        return ret;
    }
 
    ll query(ll x){
        return query(x, L, R);
    }
 
    void merge(LCTree* oth){
        if(!oth){
            return;
        }
 
        stack<LCTree*> st;
        st.push(oth);
 
        while(!st.empty()){
            LCTree* cur = st.top();
            st.pop();
            if(!cur || !cur->line){
                continue;
            }
 
            add(cur->line->m, cur->line->b);
            if(cur->lch){
                st.push(cur->lch);
            }
            if(cur->rch){
                st.push(cur->rch);
            }
        }
    }
};