struct StringHash {
    string s;
    int n, p1, p2, b1, b2;
    vector <uLL> pre1, pw1, pre2, pw2;

    void init(string _s, int _p1, int _p2, int _b1, int _b2) {
        s = _s, p1 = _p1, p2 = _p2;
        b1 = _b1, b2 = _b2;
        n = s.size();
        pre1.resize(n + 1, 0);
        pre2.resize(n + 1, 0);
        pw1.resize(n + 1, 1);
        pw2.resize(n + 1, 1);

        for (int i = 1; i <= n; ++i) {
            pre1[i] = ((pre1[i - 1] * p1) + s[i - 1]) % b1;
        }
        for (int i = 1; i <= n; ++i) {
            pw1[i] = pw1[i - 1] * p1 % b1;
        }
        for (int i = 1; i <= n; ++i) {
            pre2[i] = ((pre2[i - 1] * p2) + s[i - 1]) % b2;
        }
        for (int i = 1; i <= n; ++i) {
            pw2[i] = pw2[i - 1] * p2 % b2;
        }
    }

    uLL query1(int l, int r) {
        return (pre1[r] - (pre1[l - 1] * pw1[r - l + 1]) % b1 + b1) % b1;;
    }

    uLL query2(int l, int r) {
        return (pre2[r] - (pre2[l - 1] * pw2[r - l + 1]) % b2 + b2) % b2;
    }
}ha1, ha2;

/*
    ha1.init(s, 1e9 + 7, 1e9 + 9, 131, 1211221);
    ha2.init(s, 1e9 + 7, 1e9 + 9, 131, 1211221);
    // s = '#' + s;
*/