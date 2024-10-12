struct Ctholly{
    struct Node{
        ll l, r;
        mutable ll v;

        Node(ll l, ll r, ll v) : l(l), r(r), v(v) {}

        bool operator< (const Node &other) const {
            return l < other.l;
        }
    };

    set<Node> tr;

    void init(int n, ll v){
        tr.insert({1, n, v});
    }

    auto split(ll id){
        auto it = tr.lower_bound(Node(id, 0, 0));
        if(it != tr.end() && it->l == id){
            return it;
        }

        it--;
        ll l = it->l, r = it->r, v = it->v;

        tr.erase(it);
        tr.insert(Node(l, id - 1, v));
        return tr.insert(Node(id, r, v)).first;
    }

    void assign(ll l, ll r, ll v){
        auto end = split(r + 1), begin = split(l);  

        tr.erase(begin, end); 
        tr.insert(Node(l, r, v));  
    }
};