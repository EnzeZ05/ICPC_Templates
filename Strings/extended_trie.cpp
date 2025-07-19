template<typename Info>
struct ExTrie{
    map<Info, ExTrie*> mp;

    void insert(const vector<Info> &tr, int pos = 0) {
        if(pos == (int)tr.size()){
            return;
        }

        Info key = tr[pos];
        if (!mp[key]) {
            mp[key] = new ExTrie();
        }
        mp[key]->insert(tr, pos + 1);
    }

    int search(const vector<Info> &tr, int pos = 0) const {
        if (pos == (int)tr.size()) {
            return true; 
        }
        auto it = mp.find(tr[pos]);
        if (it == mp.end()) {
            return false;
        }
        return it->second->search(tr, pos + 1);
    }

    void remove(const vector<Info> &tr, int pos = 0){
        if(pos == (int)tr.size()){
            return;
        }

        auto it = mp.find(tr[pos]);
        if(it == mp.end()){
            return;
        }

        int del = it->second->remove(tr, pos + 1);
        if(del){
            delete it->second;
            mp.erase(it);
        }
    }
};