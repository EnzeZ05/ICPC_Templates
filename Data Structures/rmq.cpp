struct RMQ {
    int n;
    vector<vector<int>> f;
    vector<int> w;

    const int M = 18;

    void init(int _n){
        n = _n;

        f.resize(n, {});
        w.resize(n);

        for(int i = 0; i < n; i++){
            f[i].resize(18);
        }
    }

    void upd() {
        for (int j = 0; j < M; j++) {
            for (int i = 1; i + (1 << j) - 1 < n; i++) {
                if (j == 0) {
                    f[i][j] = w[i];
                } else {
                    f[i][j] = f[i][j - 1] + f[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int qr(int l, int r) {
        int len = r - l + 1;
        int k = log2(len);
        return f[l][k] + f[r - (1 << k) + 1][k];
    }
};