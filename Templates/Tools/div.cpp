bool cmp(const string &a, const string &b) {
    if(a.size() < b.size()){ 
        return 1;
    }
    if(a.size() > b.size()){
        return 0;
    }
    return a < b;
}

string subtract(const string& a, const string& b) {
    if (a == b) return "0";

    string res;
    int l = a.size(), r = b.size();
    int br = 0, i = 0;

    while(i < l){
        int A = a[l - i - 1] - '0';
        int B = i < r ? b[r - i - 1] - '0' : 0;

        int d = A - B - br;
        if(d < 0){
            d += 10;
            br = 1;
        } 
        else {
            br = 0;
        }

        res += (d + '0');
        ++i;
    }

    while(res.size() > 1 && res.back() == '0'){
        res.pop_back();
    }

    reverse(res.begin(), res.end());
    return res;
}

pair<string, string> div(const string &a, const string &b){
    if(cmp(a, b)){
        return {"0", a};
    }

    string quot, cur, rem = "0";

    for(int i = 0; i < a.size(); ++i){
        cur += a[i];

        while(cur.size() > 1 && cur[0] == '0'){
            cur.erase(0, 1);
        }

        int q = 0;
        while(!cmp(cur, b)) {
            cur = subtract(cur, b);
            q++;
        }

        quot += (q + '0');
    }

    while(quot.size() > 1 && quot[0] == '0'){
        quot.erase(0, 1);
    }

    rem = cur.empty() ? "0" : cur;
    return {quot, rem};
}