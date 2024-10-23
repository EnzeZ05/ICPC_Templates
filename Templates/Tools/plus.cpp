string add(const string& a, const string& b) {
    string res;
    int l = a.size(), r = b.size();
    int c = 0, i = 0;

    while (i < l || i < r || c) {
        int A = i < l ? a[l - i - 1] - '0' : 0;
        int B = i < r ? b[r - i - 1] - '0' : 0;

        int sum = A + B + c;
        res += (sum % 10) + '0';
        c = sum / 10;
        ++i;
    }

    reverse(res.begin(), res.end());
    return res;
}
