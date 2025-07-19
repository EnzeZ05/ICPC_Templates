vector<int> Z(const string& s){
    int n = s.length();
    vector<int> z(n); 
    z[0] = n;
 
    for(int i = 1, c = 1, r = 1, len; i < n; i++){
        len = r > i ? chmin(r - i, z[i - c]) : 0;
        while(i + len < n && s[i + len] == s[len]){
            len++;
        }
        if(i + len > r){
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
    return z;
}

vector<int> E(const string& s, const string& t, const vector<int>& z){
    int n = s.size(), m = t.size();
    vector<int> e(n);
    for(int i = 0, c = 0, r = 0, len; i < n; i++){
        len = r > i ? chmin(r - i, z[i - c]) : 0;
        while(i + len < n && len < m && s[i + len] == t[len]){
            len++;
        }
        if(i + len > r){
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
    return e;
}