string mul(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    
    int l = a.size(), r = b.size();
    vector<int> res(l + r, 0);

    for (int i = l - 1; i >= 0; --i) {
        for (int j = r - 1; j >= 0; --j) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = mul + res[i + j + 1];

            res[i + j + 1] = sum % 10;
            res[i + j] += sum / 10;
        }
    }

    string result;
    for (int num : res) {
        if (!(result.empty() && num == 0)) {
            result += to_string(num);
        }
    }

    return result.empty() ? "0" : result;
}