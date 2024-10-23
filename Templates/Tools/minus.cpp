string subtract(const string& a, const string& b) {
    if (a == b) return "0";

    string res;
    int l = a.size(), r = b.size();
    int br = 0, i = 0;

    while (i < l) {
        int A = a[l - i - 1] - '0';
        int B = i < r ? b[r - i - 1] - '0' : 0;

        int d = A - B - br;
        if (d < 0) {
            d += 10;
            br = 1;
        } 
        else {
            br = 0;
        }

        res += (d + '0');
        ++i;
    }

    while(res.size() > 1 && res.back() == '0') {
        res.pop_back();
    }

    reverse(res.begin(), res.end());
    return res;
}