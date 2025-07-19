struct Line{
    ld m, b;  
    int idx; // (if needed for tie-breaking)
    Line(ld _m, ld _b, int _idx = 0) : m(_m), b(_b), idx(_idx) {}
    
    ld eval(ld x) const { 
        return m * x + b; 
    }
};
 
struct LCTree{
    ld L, R;      
    Line* line = nullptr; 
    LCTree *lch = nullptr, *rch = nullptr;
 
    LCTree(ld _L, ld _R) : L(_L), R(_R) {}
 
    void add(Line* nl, ld l, ld r){
        if(!line){
            line = nl;
            return;
        }
        
        if(fabs(l - r) < 1e-9){  // if the interval is extremely small
            if(nl->eval(l) > line->eval(l)){
                swap(nl, line);
            }
            return;
        }
        
        ld mid = (l + r) / 2.0;
        bool mBetter = (nl->eval(mid) > line->eval(mid));
        if(mBetter){
            swap(nl, line);
        }
        if(nl->eval(l) > line->eval(l)){
            if (!lch) {
                lch = new LCTree(l, mid);
            }
            lch->add(nl, l, mid);
        }
        else { 
            if(!rch){
                rch = new LCTree(mid, r);
            }
            rch->add(nl, mid, r);
        }
    }
 
    void add(ld m, ld b, int idx = 0){
        Line* nl = new Line(m, b, idx);
        add(nl, L, R);
    }
 
    ld query(ld x, ld l, ld r){
        ld ret = (line ? line->eval(x) : -INF);
        if(fabs(l - r) < 1e-9){
            return ret;
        }
        ld mid = (l + r) / 2.0;
        if(x < mid){
            if(lch){
                ret = chmax(ret, lch->query(x, l, mid));
            }
        }
        else{
            if(rch){
                ret = chmax(ret, rch->query(x, mid, r));
            }
        }
        return ret;
    }
 
    ld query(ld x){
        return query(x, L, R);
    }
};